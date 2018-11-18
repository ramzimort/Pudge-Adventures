#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class RotateTowardPointerEvent : public Event
{
	public:
		RotateTowardPointerEvent();
		~RotateTowardPointerEvent();

	public:
		glm::vec2 PointerPositonWorldSpace;
};