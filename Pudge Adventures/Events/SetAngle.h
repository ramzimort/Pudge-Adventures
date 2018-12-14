
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: SetAngle.h
Purpose: Event that passes rotation data to transform when rotation is called (Ballista)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

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