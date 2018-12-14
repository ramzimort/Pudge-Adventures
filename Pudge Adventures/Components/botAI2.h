
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: botAI2.h
Purpose: Component that handles computer bots (Ballista)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include <glm/vec2.hpp>

class botAI2 : public Component
{
public:
	botAI2();
	~botAI2();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objFile);

private:
	float CurrentTime;
	float AttackSpeed;

	std::string ProjectileName;
	float ProjectileSpeed;

	bool isAwake;

	glm::vec2 Ballista_Pudge;
	void CheckCamera(Event* pEvent);
	void ShootProjectile();
};