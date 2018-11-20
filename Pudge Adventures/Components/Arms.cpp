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
}

void Arms::Init()
{ 
	//gpEventManager->Subscribe(ROTATE_TOWARD_POINTER, leftArm);
	//gpEventManager->Subscribe(ROTATE_TOWARD_POINTER, hook);

	//gpEventManager->Subscribe(ROTATE_TOWARD_POINTER, rightArm);
	//gpEventManager->Subscribe(ROTATE_TOWARD_POINTER, cleaver);
}

void Arms::Update()
{
	if (isCleaving)
	{
		// Rotate Arm by angular velocity 
		rightArmAngle += PI / 100;
		if (rightArmAngle > 0.f)
		{
			rightArmAngle = 0.f;
			isCleaving = false;
		}
		SetRightArmAngle();
	}

	if (isHooking)
	{
		// extend pivottocollidervector

		//increase angle


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
		hook->HandleEvent(pEvent);
		cleaver->HandleEvent(pEvent);
		break;
	case INVOKE_CLEAVE:
		if (!isCleaving)
		{
			isCleaving = true;
			rightArmAngle = -PI;
			SetRightArmAngle();
		}
		break;
	case INVOKE_HOOK:
		if (!isHooking)
		{
			isHooking = true;
			leftArmAngle = 0.f;
			SetRightArmAngle();

			// Set Hook Velocity 
		}
		break;

	case ROTATE_TOWARD_POINTER:

		break;
	case MIRROR_OBJECT:
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