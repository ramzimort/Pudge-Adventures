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