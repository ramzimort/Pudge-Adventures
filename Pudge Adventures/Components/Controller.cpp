
#include "Controller.h"
#include "Sprite.h"
#include "GameObject.h"
#include "..\Events\Event.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Events\UpdateMouseScreenPosition.h"
#include <SDL2/SDL_scancode.h>

extern Input_Manager* gpInputManager;

Controller::Controller() : Component(CONTROLLER) , moveEnable(true)
{ }
Controller::~Controller() 
{ }
void Controller::Init()
{ }
void Controller::Update()
{
	if (moveEnable)
	{
		Sprite* pSpr = static_cast<Sprite*>(mpOwner->GetComponent(SPRITE));
		if (gpInputManager->isPressed(SDL_SCANCODE_A))
		{
			mpOwner->HandleEvent(&Event(MOVE_LEFT));
			pSpr->enableAnimation = true;
			
		}
		else if (gpInputManager->isPressed(SDL_SCANCODE_D))
		{
			mpOwner->HandleEvent(&Event(MOVE_RIGHT));
			static_cast<Sprite*>(mpOwner->GetComponent(SPRITE))->enableAnimation = true;
		}
		else
		{
			pSpr->enableAnimation = false;
			pSpr->ResetAnimation();
		}
		if (gpInputManager->isTriggered(SDL_SCANCODE_SPACE))
		{
			mpOwner->HandleEvent(&Event(JUMP));
			moveEnable = false;
			pSpr->enableAnimation = false;
			pSpr->ResetAnimation();
		}
	}
	if (gpInputManager->isTriggered(SDL_SCANCODE_Q))
	{
		// Broadcast Pointer Position
		mpOwner->HandleEvent(&UpdateMouseScreenPositionEvent((float)gpInputManager->PointerLocation()[0], (float)gpInputManager->PointerLocation()[1]));
		mpOwner->HandleEvent(&Event(INVOKE_HOOK));
	}
	if (gpInputManager->isTriggered(SDL_SCANCODE_E))
	{
		mpOwner->HandleEvent(&Event(INVOKE_CLEAVE));
	}
}
void Controller::HandleEvent(Event * pEvent)
{
	switch (pEvent->mType)
	{
	case BLOCK_MOVE:
		moveEnable = false;
		break;
	case UNBLOCK_MOVE:
		moveEnable = true;
		break;
	}
	
}