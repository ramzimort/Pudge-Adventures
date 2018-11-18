#pragma once

#include "Event.h"
#include <glm/vec2.hpp>

class InitializeBodyEvent : public Event
{
public:
	InitializeBodyEvent();
	~InitializeBodyEvent();

public:
	glm::vec2 InitialPosition;
	glm::vec2 mPivot;
	glm::vec2 mScale;
	float InitialAngle;
};