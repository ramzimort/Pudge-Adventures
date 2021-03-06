
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.h
Purpose: Frame Rate Controller (allows setting/measuring each frame's time)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <SDL2/SDL_stdinc.h>

class FrameRateController {
public:
	FrameRateController(Uint32 MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();

	float GetFrameTime();

private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mNeededTicksPerFrame;
	Uint32 mFrameTime;
};
