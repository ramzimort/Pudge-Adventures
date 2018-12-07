#pragma once

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