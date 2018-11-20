#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>

class Arms : public Component
{
public:
	Arms();
	~Arms();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);

private:
	void SetRightArmAngle();
	void SetLeftArmAngle();

private:
	GameObject* leftArm;
	GameObject*	hook;
	float leftArmAngle = 0.f;

	GameObject*	rightArm;
	GameObject*	cleaver;
	float rightArmAngle = 0.f;

	bool isCleaving = false;
	bool isHooking = false;
};