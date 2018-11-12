#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class RotateArmEvent : public Event
{
	public:
		RotateArmEvent();
		~RotateArmEvent();

	public:
		glm::vec2 pointerPos;
};