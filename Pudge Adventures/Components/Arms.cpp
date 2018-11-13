#include "Arms.h"
#include "Body.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Component_Managers\EventManager.h"
#include "GameObject.h"
#include "..\Events\Event.h"
#include "..\Events\UpdatePosition.h"
#include <iostream>

extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;

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
	gpEventManager->Subscribe(ROTATE_ARM_TOWARD_POINTER, mpArms[0]);
	//gpEventManager->Subscribe(ROTATE_ARM_TOWARD_POINTER, mpArms[1]);
}

void Arms::Update()
{

}

void Arms::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case UPDATE_BODY:
		mpArms[0]->HandleEvent(pEvent);
		mpArms[1]->HandleEvent(pEvent);
		break;
	}
}