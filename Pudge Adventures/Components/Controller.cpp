
#include "Controller.h"
#include "GameObject.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Events\Collide.h"
#include "..\Events\PlayerHit.h"
#include "..\Events\PlayerMove.h"
#include "..\Events\InvokeHook.h"
#include <SDL2/SDL_scancode.h>

extern Input_Manager* gpInputManager;

Controller::Controller() : Component(CONTROLLER) 
{ }
Controller::~Controller() 
{ }
void Controller::Init()
{ }
void Controller::Update()
{
	if (mpOwner != nullptr  && gpInputManager != nullptr) 
	{
		PlayerMoveEvent PlayerMove;
		if (gpInputManager->isPressed(SDL_SCANCODE_A)) 
		{
			PlayerMove.aType = MOVE_LEFT;
			mpOwner->HandleEvent(&PlayerMove);
		}
		if (gpInputManager->isPressed(SDL_SCANCODE_D))
		{
			PlayerMove.aType = MOVE_RIGHT;
			mpOwner->HandleEvent(&PlayerMove);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_SPACE)) 
		{		
			PlayerMove.aType = JUMP;
			mpOwner->HandleEvent(&PlayerMove);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_Q))
		{
			InvokeHookEvent InvokeHook;
			InvokeHook.pointerPos.x = (float)gpInputManager->PointerLocation()[0];
			InvokeHook.pointerPos.y = (float)gpInputManager->PointerLocation()[1];
			mpOwner->HandleEvent(&InvokeHook);
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

}