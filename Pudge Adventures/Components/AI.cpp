#include "AI.h"
#include "..\Component_Managers\FrameRateController.h"
#include "Transform.h"
#include "Body.h"
#include "GameObject.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\Event.h"

extern FrameRateController* gpFRC;

botAI::botAI() :	
	Component(BOTAI),
	changeDirectionInterval(0),
	currentTime(0) { }

botAI::~botAI() { }

void botAI::Init()
{
}

void botAI::Update()
{
	currentTime += gpFRC->GetFrameTime();
	if (currentTime > changeDirectionInterval) 
	{
		speed *= -1.f;
		currentTime = 0.f;
	}
		
	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	pTr->mPosition.x += speed * gpFRC->GetFrameTime();
}

void botAI::Serialize(std::ifstream & inFile)
{
	inFile >> changeDirectionInterval;
	inFile >> speed;
}

void botAI::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == PLAYER_HIT)
	{
		Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		if (pBody != nullptr)
		{
			pBody->mPos.x += 50;
		}
	}
}
