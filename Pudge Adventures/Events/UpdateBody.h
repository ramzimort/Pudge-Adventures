
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: RotateBody.h
Purpose: Event that passes rotation data to transform when rotation is called (Ballista)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Event.h"
#include  <glm/vec2.hpp>

class UpdateBodyEvent : public Event
{
public:
	UpdateBodyEvent() : Event(UPDATE_BODY) , newPosition(0.f) { }
	~UpdateBodyEvent() { }

public:
	glm::vec2 newPosition;
};