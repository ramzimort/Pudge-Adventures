
#include "Controller.h"
#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include <SDL2/SDL_scancode.h>
#include "..\Events\Collide.h"
#include "..\Events\PlayerHit.h"
#include "..\Events\PlayerMove.h"
#include "..\Events\RotateArm.h"

extern Input_Manager* gpInputManager;
extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;

Controller::Controller() : Component(CONTROLLER) 
{	
}

Controller::~Controller() 
{
}

void Controller::Init()
{
	gpEventManager->Subscribe(PLAYER_MOVE, this->mpOwner);
}

void Controller::Update()
{
	if (mpOwner != nullptr  && gpInputManager != nullptr) 
	{
		PlayerMoveEvent PME;
		if (gpInputManager->isPressed(SDL_SCANCODE_A)) 
		{
			PME.aType = MOVE_LEFT;
			gpEventManager->BroadcaseEventToSubscribers(&PME);
		}
		if (gpInputManager->isPressed(SDL_SCANCODE_D))
		{
			PME.aType = MOVE_RIGHT;
			gpEventManager->BroadcaseEventToSubscribers(&PME);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_SPACE)) 
		{		
			PME.aType = JUMP;
			gpEventManager->BroadcaseEventToSubscribers(&PME);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_Q))
		{
			RotateArmEvent RAE;
			RAE.pointerPos.x = (float)gpInputManager->PointerLocation()[0];
			RAE.pointerPos.y = (float)gpInputManager->PointerLocation()[1];
			gpEventManager->BroadcaseEventToSubscribers(&RAE);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_E))
		{
			//PIE.aType = CLEAVE;
			//gpEventManager->BroadcaseEventToSubscribers(&PIE);
		}
	}

}

void Controller::HandleEvent(Event * pEvent)
{
	if (COLLIDE == pEvent->mType)
	{
		CollideEvent* pRealEvent = static_cast<CollideEvent*>(pEvent);
		Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		if (pBody != nullptr)
			pBody->mPos.x = 0.0f;
		PlayerHitEvent* phe = new PlayerHitEvent();
		phe->mTimer = 1.0f;
		gpEventManager->AddTimeEvent(phe);
	}
}