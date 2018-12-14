
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PowerUp.h
Purpose: Contains information on rune object (its type)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"

enum RuneType
{
	REGEN,
	HASTE,
	DD
};

class PowerUp : public Component
{
public:
	PowerUp();
	~PowerUp();

	void Init();
	void Update();
	void Serialize(rapidjson::Document& objFile);
	void HandleEvent(Event* pEvent);
public:
	RuneType mType;
};