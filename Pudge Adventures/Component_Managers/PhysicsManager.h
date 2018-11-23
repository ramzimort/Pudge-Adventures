#pragma once
#include "EventManager.h"
#include "..\Components\Body.h"


class PhysicsManager
{
	public:
		PhysicsManager();
		~PhysicsManager();

		void Init();
		void Update(float FrameTime);

		void(*InteractionTypes[BODYNUM][BODYNUM])(Body* pBody1, Body* pBody2, glm::vec2& offset);
};