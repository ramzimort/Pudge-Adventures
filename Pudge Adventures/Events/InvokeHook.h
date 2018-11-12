#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

class InvokeHookEvent : public Event
{
	public:
		InvokeHookEvent();
		~InvokeHookEvent();

	public:
		glm::vec2 pointerPos;
};