#pragma once

#include "Event.h" 
#include <glm/vec2.hpp>
class RotateBodyEvent : public Event
{
public:
	RotateBodyEvent() : Event(ROTATE_BODY) { }
	~RotateBodyEvent() { }
public:
	glm::vec2 mPivot;
	float deltaAngle;
};