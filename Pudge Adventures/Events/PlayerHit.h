#pragma once

#include "Event.h"

class PlayerHitEvent : public Event
{
public:
	PlayerHitEvent();
	~PlayerHitEvent() { }
};