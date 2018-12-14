
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CameraMove.h
Purpose: Event passed to objects when camera moves (backgrounds use it to scroll at different speeds, AI use it to wake up)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

class CameraMoveEvent : public Event
{
public:
	CameraMoveEvent() : Event(CAMERA_MOVE), deltaX(0.f), currentPos(0.f), SCR_WIDTH(0.f), SCR_HEIGHT(0.f) { }
	~CameraMoveEvent() { }

public:
	float deltaX;
	glm::vec2 currentPos;
	float SCR_WIDTH;
	float SCR_HEIGHT;
};