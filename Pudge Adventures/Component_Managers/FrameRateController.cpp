
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.cpp
Purpose: Frame Rate Controller implementation
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#include "FrameRateController.h"
#include <SDL2/SDL_timer.h>

FrameRateController::FrameRateController(Uint32 MaxFramerate) {
	mTickEnd = mTickStart = mFrameTime = 0;
	if (0 != MaxFramerate)
		mNeededTicksPerFrame = 1000 / MaxFramerate;
	else
		mNeededTicksPerFrame = 0;
}

FrameRateController::~FrameRateController() {

}


void FrameRateController::FrameStart() {
	mTickStart = SDL_GetTicks();
}

void FrameRateController::FrameEnd() {
	mTickEnd = SDL_GetTicks();
	while ((mTickEnd - mTickStart) < mNeededTicksPerFrame)
		mTickEnd = SDL_GetTicks();

	mFrameTime = mTickEnd - mTickStart;
}

float FrameRateController::GetFrameTime() {
	return mFrameTime/1000;
}