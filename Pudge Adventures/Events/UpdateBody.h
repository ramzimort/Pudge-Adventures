#pragma once

#include "Event.h"
#include  <glm/vec2.hpp>

class UpdateBodyEvent : public Event
{
public:
	UpdateBodyEvent();
	~UpdateBodyEvent();

public:
	glm::vec2 newPosition;
};