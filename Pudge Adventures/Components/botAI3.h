
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: botAI3.h
Purpose: Component that handles computer bots (Wyvern)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/
#pragma once

#include "Component.h"
#include <glm/vec2.hpp>

class botAI3 : public Component
{
public:
	botAI3();
	~botAI3();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objFile);

private:
	float MoveSpeed;
	
	float AttackSpeed;
	float CurrentTime;


	float ProjectileSpeed;
	glm::vec2 ProjectileOffset;
	std::string ProjectileName;

	bool isAwake;

	glm::vec2 Shooter_Pudge;
	float camLeft, camRight;

private:
	void CheckCamera(Event* pEvent);
	void ShootProjectile();
	float findAcuteAngle(glm::vec2 const& V1, glm::vec2 const& V2);
};