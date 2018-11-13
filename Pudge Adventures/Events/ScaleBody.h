#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class ScaleBodyEvent : public Event
{
public:
	ScaleBodyEvent();
	~ScaleBodyEvent();
public:
	glm::vec2 mScale;
};