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
#include "..\Component_Managers\GameObjectManager.h"
#include <iostream>

extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;
extern GameObjectManager* gpGameObjectManager;

Arms::Arms() : Component(ARMS)
{ }

Arms::~Arms()
{ }

void Arms::Serialize(rapidjson::Document& objectFile)
{
	std::string leftArmFile = objectFile["Arms"]["LeftArm"].GetString();
	mpArms[0] = gpObjectFactory->LoadObject(leftArmFile);
	std::string rightArmFile = objectFile["Arms"]["RightArm"].GetString();
	mpArms[1] = gpObjectFactory->LoadObject(rightArmFile);
}

void Arms::Init()
{ 
	gpEventManager->Subscribe(ROTATE_TOWARD_POINTER, mpArms[0]);
//	gpEventManager->Subscribe(ROTATE_ARM_TOWARD_POINTER, mpArms[1]);
}

void Arms::Update()
{

}

void Arms::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	//case INITIALIZE_BODY:
	case UPDATE_BODY:
		mpArms[0]->HandleEvent(pEvent);
		mpArms[1]->HandleEvent(pEvent);
		break;
	case MIRROR_OBJECT:
		mpArms[0]->HandleEvent(pEvent);
		mpArms[1]->HandleEvent(pEvent);
		gpGameObjectManager->mGameObjects.erase(mpArms[0]);
		gpGameObjectManager->mGameObjects.erase(mpArms[1]);
		std::swap(static_cast<Transform*>(mpArms[0]->GetComponent(TRANSFORM))->zValue,
			(static_cast<Transform*>(mpArms[1]->GetComponent(TRANSFORM))->zValue));
		gpGameObjectManager->mGameObjects.insert(mpArms[0]);
		gpGameObjectManager->mGameObjects.insert(mpArms[1]);
		break;
	}
}