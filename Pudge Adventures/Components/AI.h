#pragma once

#include "Component.h"

#include <fstream>

class botAI : public Component
{
	public:
		botAI();
		~botAI();

		void Init();
		void Update();
		void Serialize(std::ifstream& inFile);
		void HandleEvent(Event* pEvent);

	public:
		float changeDirectionInterval;
		float speed;
		float currentTime;
};