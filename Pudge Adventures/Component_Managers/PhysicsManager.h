#pragma once
#include "EventManager.h"
#include "..\Components\Body.h"

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: PhysicsManager.h
Purpose: Handles interactions when collisions between objects occur
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

class PhysicsManager
{
	public:
		PhysicsManager();
		~PhysicsManager();

		void Init();
		void Update(float FrameTime);

		void(*InteractionTypes[BODYNUM][BODYNUM])(Body* pBody1, Body* pBody2, glm::vec2& offset);
};