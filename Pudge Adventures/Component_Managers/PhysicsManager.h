#pragma once
#include "EventManager.h"



class PhysicsManager
{
	public:
		PhysicsManager();
		~PhysicsManager();

		void Init();
		void Update(float FrameTime);
};