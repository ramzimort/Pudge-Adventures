#include "Arms.h"
#include "Body.h"
#include "Transform.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Component_Managers\EventManager.h"
#include "GameObject.h"
#include "..\Events\Event.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\MIrrorArms.h"
#include "..\Events\MirrorObject.h"
#include "..\Events\SetAngle.h"
#include "..\Events\UpdateMouseWorldPosition.h"
#include "..\Component_Managers\GameObjectManager.h"
#include <iostream>

extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;

constexpr float PI = 3.14159265358979323846f;

Arms::Arms() : Component(ARMS)
{ }

Arms::~Arms()
{ }

void Arms::Serialize(rapidjson::Document& objectFile)
{
	std::string objectFileName;
	objectFileName = objectFile["Arms"]["LeftArm"].GetString();
	leftArm = gpObjectFactory->LoadObject(objectFileName);

	objectFileName = objectFile["Arms"]["RightArm"].GetString();
	rightArm = gpObjectFactory->LoadObject(objectFileName);

	objectFileName = objectFile["Arms"]["LeftArmWeapon"].GetString();
	hook = gpObjectFactory->LoadObject(objectFileName);

	objectFileName = objectFile["Arms"]["RightArmWeapon"].GetString();
	cleaver = gpObjectFactory->LoadObject(objectFileName);

	leftArmRotationSpeed = PI / 10;
	rightArmRotationSpeed = PI / 100;
	hookSpeed = 500.f;
}

void Arms::Init()
{ 
	leftArm->Init();
	pivotToCollider_ReferenceL = (static_cast<Body*>(leftArm->GetComponent(BODY))->mPivot_mColliderCenter);
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
		}
		SetRightArmAngle();
	}

	// Hook Arm Animation (NOT SAME AS WAITING FOR HOOK)
	if (isHooking)
	{
		leftArmAngle -= leftArmRotationSpeed;
		if (leftArmAngle < leftArmFinalAngle)
		{
			leftArmAngle = leftArmFinalAngle;
			isHooking = false;

			// Throw Hook
			isWaitingHook = true;
		}
		SetLeftArmAngle();
	}

	if (isWaitingHook)
	{
		glm::vec2 hookDirection = static_cast<Body*>(hook->GetComponent(BODY))->mPivot_mColliderCenter;
		static_cast<Body*>(hook->GetComponent(BODY))->mVel = hookSpeed * hookDirection / glm::length(hookDirection);
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
			rightArmAngle = -PI;
			rightArmFinalAngle = 0.f;
			SetRightArmAngle();
		}
		break;
	case INVOKE_HOOK:
		if (!isHooking)
		{
			isHooking = true;			

			// Check if Mirroring required
			glm::vec2 pivotToMouse = mousePos - (static_cast<Body*>(leftArm->GetComponent(BODY))->mPos + static_cast<Body*>(leftArm->GetComponent(BODY))->mPos_mPivot);
			if (pivotToMouse.x > 0.f && !isMirrored || pivotToMouse.x < 0.f && isMirrored)
			{
				MirrorObjectEvent MirrorObject;
				mpOwner->HandleEvent(&MirrorObject);
			}
			// Update Pivot to Mouse after Mirroring
			pivotToMouse = mousePos - (static_cast<Body*>(mpOwner->GetComponent(BODY))->mPos + static_cast<Body*>(leftArm->GetComponent(BODY))->mPos_mPivot);
			std::cout << pivotToMouse.x << std::endl;

			/* ================================================= Get Angle for Arm Rotation ===================================================================*/
			glm::vec2 v1 = glm::normalize(pivotToCollider_ReferenceL);
			glm::vec2 v2 = glm::normalize(pivotToMouse);

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
			if (isMirrored)
				newAngle *= -1.f;

			/* ================================================= Initiate Animation Variables ===================================================================*/
			leftArmAngle = 0.f;
			SetLeftArmAngle();
			leftArmFinalAngle = newAngle;

			/* ================================================= Block Movement Inputs ===================================================================*/
		}
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