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