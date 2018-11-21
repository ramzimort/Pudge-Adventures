#pragma once

#include "Event.h"

class InvokeCleaveEvent : public Event
{
public:
	InvokeCleaveEvent() : Event(INVOKE_CLEAVE) { }
	~InvokeCleaveEvent() { }
};