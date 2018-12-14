
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ApplyDamage.h
Purpose: Event passed to object when damage is applied to it (Either by collision of projectile or hook/cleave)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Event.h"

class ApplyDamageEvent : public Event
{
public:
	ApplyDamageEvent(float _damage) : Event(APPLY_DAMAGE), damage(_damage) { }
public:
	float damage;
};