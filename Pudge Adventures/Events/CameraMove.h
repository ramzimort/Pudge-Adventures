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