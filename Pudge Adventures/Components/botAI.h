
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: botAI.h
Purpose: Component that handles computer bots (Creeps)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/


#pragma once

#include "Component.h"
#include <glm/glm.hpp>

#include <fstream>

class botAI : public Component
{
	public:
		botAI();
		~botAI();

		void Init();
		void Update();
		void Serialize(rapidjson::Document& objectFile);
		void HandleEvent(Event* pEvent);

	public:
		float changeDirectionInterval;
		float speed;
		float projectileSpeed;
		float currentTime;
		bool isAwake;

		glm::vec2 ProjectileOffset;

		std::string ProjectileName;
private:
	void ShootProjectile();
	void CheckCamera(Event* pEvent);
};