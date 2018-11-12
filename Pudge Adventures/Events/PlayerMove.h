#pragma once

#include "Event.h"
#include <glm/glm.hpp>

enum actionType {
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
};

class PlayerMoveEvent : public Event 
{
	public:
		PlayerMoveEvent();
		~PlayerMoveEvent() { }
	public:
		actionType aType;
};