#pragma once

#include "Event.h"
#include "glm/vec2.hpp"

class CameraMoveEvent : public Event
{
public:
	CameraMoveEvent();
	~CameraMoveEvent();

public:
	float deltaX;
};