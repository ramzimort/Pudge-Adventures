
#include "Controller.h"
#include "GameObject.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Events\Collide.h"
#include "..\Events\PlayerHit.h"
#include "..\Events\PlayerMove.h"
#include "..\Events\InvokeHook.h"
#include "..\Events\InvokeCleave.h"
#include "..\Events\UpdateMouseScreenPosition.h"
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
			// Broadcast Pointer Position
			UpdateMouseScreenPositionEvent UpdateMouseScreenPosition((float)gpInputManager->PointerLocation()[0], (float)gpInputManager->PointerLocation()[1]);
			mpOwner->HandleEvent(&UpdateMouseScreenPosition);
			InvokeHookEvent InvokeHook;
			mpOwner->HandleEvent(&InvokeHook);
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_E))
		{
			InvokeCleaveEvent InvokeCleave;
			mpOwner->HandleEvent(&InvokeCleave);
		}
	}

}
void Controller::HandleEvent(Event * pEvent)
{

}