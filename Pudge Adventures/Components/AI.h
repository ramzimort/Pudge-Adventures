#pragma once

#include "Component.h"

#include <fstream>

class botAI : public Component
{
	public:
		botAI();
		~botAI();

		void Update();
		void Serialize(std::ifstream& inFile);

	public:
		float changeDirectionInterval;
		float speed;
		float currentTime;
};