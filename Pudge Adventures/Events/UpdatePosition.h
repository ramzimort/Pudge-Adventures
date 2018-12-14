
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UpdatePosition.h
Purpose: Updates position of object (Usually only used with arms to pass poition from parent body to attached bodies).
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Event.h"
#include <glm/glm.hpp>

class UpdatePositionEvent : public Event
{
public:
	UpdatePositionEvent() :	Event(UPDATE_POSITION),	newPosition(0.f),newAngle(0.f) { }
	~UpdatePositionEvent() { }

public:
	glm::vec2 newPosition;
	float newAngle;
};