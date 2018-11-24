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