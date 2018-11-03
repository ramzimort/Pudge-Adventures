
#include "Controller.h"
#include "Transform.h"
#include "GameObject.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Include\SDL2\SDL_scancode.h"

extern Input_Manager* gpInputManager;
extern FrameRateController* gpFRC;

Controller::Controller() : Component(CONTROLLER) {
	
}

Controller::~Controller() {

}

void Controller::Update() 
{
	if (mpOwner != nullptr  && gpInputManager != nullptr) {
		Transform *pTr = static_cast<Transform*>(mpOwner->GetComponent(COMPONENT_TYPE::TRANSFORM));
		if (pTr != nullptr) {
			if (gpInputManager->isPressed(SDL_SCANCODE_W)) {				// When you press W
				pTr->mPosition.y += gpFRC->GetFrameTime() * 100 ;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_S)) {				// When you press S
				pTr->mPosition.y -= gpFRC->GetFrameTime() * 100;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_A)) {				// When you press A
				pTr->mPosition.x -= gpFRC->GetFrameTime() * 100;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_D)) {				// When you press D
				pTr->mPosition.x += gpFRC->GetFrameTime() * 100;
			}
		}
	}

}