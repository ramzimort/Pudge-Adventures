#include "Arms.h"
#include "Body.h"
#include "Transform.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Component_Managers\EventManager.h"
#include "GameObject.h"
#include "..\Events\Event.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\SetAngle.h"
#include "..\Events\UpdateMouseWorldPosition.h"
#include "..\Component_Managers\GameObjectManager.h"
#include <iostream>

extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;

constexpr float PI = 3.14159265358979323846f;
float findAcuteAngle(glm::vec2&, glm::vec2&);

Arms::Arms() : Component(ARMS)
{ }
Arms::~Arms()
{ 
	gpGameObjectManager->toBeDeleted.push(leftArm);
	gpGameObjectManager->toBeDeleted.push(rightArm);
	gpGameObjectManager->toBeDeleted.push(hook);
	gpGameObjectManager->toBeDeleted.push(cleaver);

	gpEventManager->Unsubscribe(RETURN_HOOK, mpOwner);
	gpEventManager->Unsubscribe(GRAB_HOOK, mpOwner);
}
void Arms::Serialize(rapidjson::Document& objectFile)
{
	std::string objectFileName;
	objectFileName = objectFile["Arms"]["LeftArm"].GetString();
	leftArm = gpObjectFactory->LoadObject(objectFileName);
	leftArm->Init();

	objectFileName = objectFile["Arms"]["RightArm"].GetString();
	rightArm = gpObjectFactory->LoadObject(objectFileName);
	rightArm->Init();

	objectFileName = objectFile["Arms"]["LeftArmWeapon"].GetString();
	hook = gpObjectFactory->LoadObject(objectFileName);
	hook->Init();

	objectFileName = objectFile["Arms"]["RightArmWeapon"].GetString();
	cleaver = gpObjectFactory->LoadObject(objectFileName);
	cleaver->Init();

	std::string componentValueName;
	for (auto& ComponentValues : objectFile["Arms"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "LeftArmRotationSpeed")
			leftArmRotationSpeed = ComponentValues.value.GetFloat()*(PI / 180.f);
		else if (componentValueName == "HookSpeed")
			hookSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "HookReturnTime")
			hookReturnTime = ComponentValues.value.GetFloat();
		else if (componentValueName == "RightArmRotationSpeed")
			rightArmRotationSpeed = ComponentValues.value.GetFloat()*(PI / 180.f);
	}	
}

void Arms::Init()
{ 
	gpEventManager->Subscribe(RETURN_HOOK, mpOwner);
	gpEventManager->Subscribe(GRAB_HOOK, mpOwner);

	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	if(pBody != nullptr)
		pivotToCollider_ReferenceL = (static_cast<Body*>(hook->GetComponent(BODY))->mPivot_mColliderCenter);

	static_cast<Body*>(hook->GetComponent(BODY))->mType = NONE;
}

void Arms::Update()
{
	// Cleave Arm Animation
	if (isCleaving)
	{
		// Rotate Arm by angular velocity 
		rightArmAngle += rightArmRotationSpeed;
		if (rightArmAngle > rightArmFinalAngle)
		{
			rightArmAngle = rightArmFinalAngle;
			isCleaving = false;
			static_cast<Body*>(cleaver->GetComponent(BODY))->mType = NONE;
		}
		SetRightArmAngle();
	}

	// Hook Arm Animation (NOT SAME AS WAITING FOR HOOK)
	if (isHooking)
	{
		// Block Movement
		mpOwner->HandleEvent(&Event(BLOCK_MOVE));

		leftArmAngle -= leftArmRotationSpeed;
		if (leftArmAngle < leftArmFinalAngle)
		{
			leftArmAngle = leftArmFinalAngle;
			isHooking = false;

			// Throw Hook
			isWaitingHook = true;
		}
		SetLeftArmAngle();
		
		if (isWaitingHook)
		{
			// Block Movement
			mpOwner->HandleEvent(&Event(BLOCK_MOVE));
			// Set timer for hook return event
			Event* ReturnHook = new Event(RETURN_HOOK);
			ReturnHook->mTimer = hookReturnTime;
			gpEventManager->AddTimeEvent(ReturnHook);

			glm::vec2 hookDirection = static_cast<Body*>(hook->GetComponent(BODY))->mPivot_mColliderCenter;
			static_cast<Body*>(hook->GetComponent(BODY))->mVel = hookSpeed * hookDirection / glm::length(hookDirection);
			static_cast<Body*>(hook->GetComponent(BODY))->mType = HOOK;
		}
	}

	if (isWaitingHook)
	{
		static_cast<Body*>(mpOwner->GetComponent(BODY))->mInvMass = 0.f;
		static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel = glm::vec2(0.f);
	}

}

void Arms::HandleEvent(Event* pEvent)
{
	Transform* pTrLeft = static_cast<Transform*>(leftArm->GetComponent(TRANSFORM));
	Transform* pTrRight = static_cast<Transform*>(rightArm->GetComponent(TRANSFORM));
	switch (pEvent->mType)
	{
	case UPDATE_BODY:
		//Update position of arms and weapons to follow pudge
		leftArm->HandleEvent(pEvent);
		rightArm->HandleEvent(pEvent);
		cleaver->HandleEvent(pEvent);
		if(!isWaitingHook)
			hook->HandleEvent(pEvent);
		break;
	case INVOKE_CLEAVE:
		if (!isCleaving)
		{
			isCleaving = true;
			static_cast<Body*>(cleaver->GetComponent(BODY))->mType = CLEAVER;
			rightArmAngle = -PI;
			rightArmFinalAngle = 0.f;
			SetRightArmAngle();
		}
		break;
	case INVOKE_HOOK:
		if (!(isHooking || isWaitingHook))
		{
			isHooking = true;			
			// Block all input
			mpOwner->HandleEvent(&Event(BLOCK_MOVE));

			// Check if Mirroring required
			glm::vec2 pivotToMouse = mousePos - (static_cast<Body*>(hook->GetComponent(BODY))->mPos + static_cast<Body*>(hook->GetComponent(BODY))->mPos_mPivot);
			if (pivotToMouse.x > 0.f && !isMirrored || pivotToMouse.x < 0.f && isMirrored)
				mpOwner->HandleEvent(&Event(MIRROR_OBJECT));
			// Update Pivot to Mouse after Mirroring
			pivotToMouse = mousePos - (static_cast<Body*>(hook->GetComponent(BODY))->mPos + static_cast<Body*>(hook->GetComponent(BODY))->mPos_mPivot);
			/* ================================================= Get Angle for Arm Rotation ===================================================================*/

			float newAngle = findAcuteAngle(pivotToCollider_ReferenceL, pivotToMouse);
			if (isMirrored)
				newAngle *= -1.f;

			/* ================================================= Initiate Animation Variables ===================================================================*/
			leftArmAngle = 0.f;
			SetLeftArmAngle();
			leftArmFinalAngle = newAngle;

			/* ================================================= Block Movement Inputs ===================================================================*/
		}
		break;
	case RETURN_HOOK:
		static_cast<Body*>(hook->GetComponent(BODY))->mVel *= -1.f;
		break;
	case GRAB_HOOK:
		isHooking = false;
		isWaitingHook = false;
		static_cast<Body*>(mpOwner->GetComponent(BODY))->mInvMass = 1.f/ static_cast<Body*>(mpOwner->GetComponent(BODY))->mMass;
		leftArmAngle = 0.f;
		SetLeftArmAngle();
		static_cast<Body*>(hook->GetComponent(BODY))->mVel = glm::vec2(0.f);
		static_cast<Body*>(hook->GetComponent(BODY))->mType = NONE;

		// Unblock all input
		mpOwner->HandleEvent(&Event(UNBLOCK_MOVE));
		break;
	case UPDATE_MOUSE_WORLD_POSITION:
		mousePos = static_cast<UpdateMouseWorldPositionEvent*>(pEvent)->MouseWorldPositon;
		break;
	case MIRROR_OBJECT:
		// Reverse isMirrored
		isMirrored = !isMirrored;
		// Reverse Collider x offset
		pivotToCollider_ReferenceL.x *= -1.f;
		// Mirror Scales and Colliders in attachments
		leftArm->HandleEvent(pEvent);
		rightArm->HandleEvent(pEvent);
		hook->HandleEvent(pEvent);
		cleaver->HandleEvent(pEvent);
		// Swap Arms
		gpGameObjectManager->mGameObjects.erase(leftArm);
		gpGameObjectManager->mGameObjects.erase(rightArm);
		std::swap(static_cast<Transform*>(leftArm->GetComponent(TRANSFORM))->zValue,
			(static_cast<Transform*>(rightArm->GetComponent(TRANSFORM))->zValue));
		gpGameObjectManager->mGameObjects.insert(leftArm);
		gpGameObjectManager->mGameObjects.insert(rightArm);
		// Swap Weapons
		gpGameObjectManager->mGameObjects.erase(hook);
		gpGameObjectManager->mGameObjects.erase(cleaver);
		std::swap(static_cast<Transform*>(hook->GetComponent(TRANSFORM))->zValue,
			(static_cast<Transform*>(cleaver->GetComponent(TRANSFORM))->zValue));
		gpGameObjectManager->mGameObjects.insert(hook);
		gpGameObjectManager->mGameObjects.insert(cleaver);
		break;
	case ENABLE_DD:
		hook->HandleEvent(&Event(ENABLE_DD));
		cleaver->HandleEvent(&Event(ENABLE_DD));
		break;
	case DISABLE_DD:
		hook->HandleEvent(&Event(DISABLE_DD));
		cleaver->HandleEvent(&Event(DISABLE_DD));
		break;
	}
}

void Arms::SetLeftArmAngle()
{
	SetAngleEvent SetAngle(leftArmAngle);
	leftArm->HandleEvent(&SetAngle);
	hook->HandleEvent(&SetAngle);
}
void Arms::SetRightArmAngle()
{
	SetAngleEvent SetAngle(rightArmAngle);
	rightArm->HandleEvent(&SetAngle);
	cleaver->HandleEvent(&SetAngle);
}

float findAcuteAngle(glm::vec2& V1, glm::vec2& V2)
{
	glm::vec2 v1 = glm::normalize(V1);
	glm::vec2 v2 = glm::normalize(V2);

	// Get proper angle
	float dotProduct = glm::dot(v1, v2);
	float newAngle;
	if (dotProduct > 1.f)
		newAngle = 0.f;
	else if (dotProduct < -1.f)
		newAngle = PI;
	else
		newAngle = acosf(dotProduct);

	glm::vec2 n1;
	n1.x = -1.f * v1.y;
	n1.y = v1.x;

	if (glm::dot(n1, v2) < 0)
		newAngle *= -1.f;

	return newAngle;
}