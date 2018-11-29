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