#pragma once

#include "Event.h"

class SetAngleEvent : public Event
{
public :
	SetAngleEvent(float angle) : Event(SET_ANGLE), mAngle(angle) { }
	~SetAngleEvent() { }

public:
	float mAngle;
};