#include "AI.h"
#include "..\Component_Managers\FrameRateController.h"
#include "Transform.h"
#include "GameObject.h"


extern FrameRateController* gpFRC;

botAI::botAI() :	Component(BOTAI),
					changeDirectionInterval(0),
					currentTime(0) {}

botAI::~botAI()
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
