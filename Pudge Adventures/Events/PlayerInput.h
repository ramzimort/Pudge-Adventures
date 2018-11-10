#pragma once

#include "Event.h"

enum actionType {
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	HOOK,
	CLEAVE
};

class PlayerInputEvent : public Event 
{
	public:
		PlayerInputEvent();
		~PlayerInputEvent() { }
	public:
		actionType aType;
};