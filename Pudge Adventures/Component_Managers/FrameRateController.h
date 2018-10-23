
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.h
Purpose: Frame Rate Controller (allows measuring each frame's time)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#ifndef FRAME_RATE_CONTROLLER_H
#define FRAME_RATE_CONTROLLER_H

#include "SDL_stdinc.h"

class FrameRateController{
public:
	FrameRateController(Uint32 MaxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();

	Uint32 GetFrameTime();

private:
	Uint32 mTickStart;
	Uint32 mTickEnd;
	Uint32 mNeededTicksPerFrame;
	Uint32 mFrameTime;

};
#endif // ! FRAME_RATE_CONTROLLER_H
