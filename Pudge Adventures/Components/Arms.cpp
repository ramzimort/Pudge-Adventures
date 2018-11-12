#include "Arms.h"
#include "Body.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Component_Managers\EventManager.h"
#include "GameObject.h"
#include "..\Events\Event.h"
#include <iostream>

extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;

Arms::Arms() : Component(ARMS)
{ }

Arms::~Arms()
{ }

void Arms::Serialize(rapidjson::Document& objectFile)
{
	std::string leftLimbFile = objectFile["Arms"]["LeftArm"].GetString();
	mpArms[0] = gpObjectFactory->LoadObject(leftLimbFile);
	std::string rightLimbFile = objectFile["Arms"]["RightArm"].GetString();
	mpArms[1] = gpObjectFactory->LoadObject(rightLimbFile);
}

void Arms::Init()
{ 
	gpEventManager->Subscribe(ROTATE_ARM, mpArms[0]);
	gpEventManager->Subscribe(ROTATE_ARM, mpArms[1]);
}

void Arms::Update()
{
	Body* pMainBodyTr = static_cast<Body*>(mpOwner->GetComponent(BODY));
	Body* pLeftArmTr = static_cast<Body*>(mpArms[0]->GetComponent(BODY));
	Body* pRightArmTr = static_cast<Body*>(mpArms[1]->GetComponent(BODY));
	
	pRightArmTr->mPos = pMainBodyTr->mPos;
	pLeftArmTr->mPos = pMainBodyTr->mPos;
}