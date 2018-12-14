
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: UpdateMouseScreenPosition.h
Purpose: Provides information of mouse in screen space
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class UpdateMouseScreenPositionEvent : public Event
{
public:
	UpdateMouseScreenPositionEvent(float xPos, float yPos) : Event(UPDATE_MOUSE_SCREEN_POSITION) , MouseScreenPosition(xPos,yPos) { }
	~UpdateMouseScreenPositionEvent() { }

public:
	glm::vec2 MouseScreenPosition;
};