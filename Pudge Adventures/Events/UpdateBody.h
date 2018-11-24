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