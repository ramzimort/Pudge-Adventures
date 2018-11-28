#pragma once

#include "Event.h"

class ApplyDamageEvent : public Event
{
public:
	ApplyDamageEvent(float _damage) : Event(APPLY_DAMAGE), damage(_damage) { }
public:
	float damage;
};