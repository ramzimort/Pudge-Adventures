#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class RotateArmTowardPointerEvent : public Event
{
	public:
		RotateArmTowardPointerEvent();
		~RotateArmTowardPointerEvent();

	public:
		glm::vec2 pointerPos;
		glm::vec2 cameraCenter;
		int SCR_WIDTH;
		int SCR_HEIGHT;
};