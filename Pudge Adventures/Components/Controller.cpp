
#include "Controller.h"
#include "..\Component_Managers\Input Manager.h"
#include "..\Components\Transform.h"
#include "..\Include\SDL2\SDL_scancode.h"

extern Input_Manager* gpInputManager;

Controller::Controller() {
	mpOwner = nullptr;
}

Controller::~Controller() {
	
}

void Controller::Update() {
	if (nullptr != mpOwner && nullptr != gpInputManager) {
		if (nullptr != mpOwner->mpTransform) {
			// If key press
			if (gpInputManager->isReleased(SDL_SCANCODE_UP)) {			// When you press up
				pImage = pResourceManager->LoadSurface("..\\Resources\\Up.bmp");
			}
			else
				if (gpInputManager->isReleased(SDL_SCANCODE_DOWN)) {			// When you press down
					pImage = pResourceManager->LoadSurface("..\\Resources\\Down.bmp");
				}
				else
					if (gpInputManager->isReleased(SDL_SCANCODE_LEFT)) {			// When you press left
						pImage = pResourceManager->LoadSurface("..\\Resources\\Left.bmp");
					}
					else
						if (gpInputManager->isReleased(SDL_SCANCODE_RIGHT)) {		// When you press right
							pImage = pResourceManager->LoadSurface("..\\Resources\\Right.bmp");
						}
						else
							if (gpInputManager->isReleased(SDL_SCANCODE_ESCAPE)) {		// When you press escape
								appIsRunning = false;
							}
							else
								if (gpInputManager->isPressed(SDL_SCANCODE_W)) {				// When you press W
									posY -= moveSpeed * pFRC->GetFrameTime();
								}
								else
									if (gpInputManager->isPressed(SDL_SCANCODE_S)) {				// When you press S
										posY += moveSpeed * pFRC->GetFrameTime();
									}
									else
										if (gpInputManager->isPressed(SDL_SCANCODE_A)) {				// When you press A
											posX -= moveSpeed * pFRC->GetFrameTime();
										}
										else
											if (gpInputManager->isPressed(SDL_SCANCODE_D)) {				// When you press D
												posX += moveSpeed * pFRC->GetFrameTime();
											}
		}
	}

}