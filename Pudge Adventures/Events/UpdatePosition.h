#pragma once

#include "Event.h"
#include <glm/glm.hpp>

class UpdatePositionEvent : public Event
{
public:
	UpdatePositionEvent();
	~UpdatePositionEvent();

public:
	glm::vec2 newPosition;
	float newAngle;
};