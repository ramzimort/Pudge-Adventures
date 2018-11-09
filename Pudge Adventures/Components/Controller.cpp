
#include "Controller.h"
#include "Body.h"
#include "GameObject.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include <SDL2/SDL_scancode.h>

extern Input_Manager* gpInputManager;
extern FrameRateController* gpFRC;

Controller::Controller() : Component(CONTROLLER) {
	
}

Controller::~Controller() {

}

void Controller::Update() 
{
	if (mpOwner != nullptr  && gpInputManager != nullptr) {
		Body *pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		if (pBody != nullptr) {
			if (gpInputManager->isPressed(SDL_SCANCODE_W)) {				// When you press W
				pBody->mForce.y = 100.f;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_S)) {				// When you press S
				pBody->mForce.y = -100.f;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_A)) {				// When you press A
				pBody->mForce.x = -100.f;
			}
			else
			if (gpInputManager->isPressed(SDL_SCANCODE_D)) {				// When you press D
				pBody->mForce.x = 100.f;
			}
		}
	}

}