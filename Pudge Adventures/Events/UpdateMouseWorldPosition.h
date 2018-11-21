#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class UpdateMouseWorldPositionEvent : public Event
{
public:
	UpdateMouseWorldPositionEvent(glm::vec2& MouseWorldPos) : Event(UPDATE_MOUSE_WORLD_POSITION), MouseWorldPositon(MouseWorldPos) { }
	~UpdateMouseWorldPositionEvent() { }

public:
	glm::vec2 MouseWorldPositon;
};