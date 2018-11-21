#pragma once

#include "Event.h"

class ReturnHookEvent : public Event
{
public:
	ReturnHookEvent(float timer) : Event(RETURN_HOOK) { mTimer = timer; }
	~ReturnHookEvent() { }
	
};