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
	/* =============== Left Arm Data =================== */
	GameObject* leftArm;
	GameObject*	hook;
	float leftArmAngle = 0.f;
	float leftArmFinalAngle = 0.f;
	float leftArmRotationSpeed = 0.f;
	glm::vec2 pivotToCollider_ReferenceL;
	float hookSpeed;
	float hookReturnTime;
	bool isHooking = false;
	bool isWaitingHook = false;

	/* =============== Right Arm Data =================== */
	GameObject*	rightArm;
	GameObject*	cleaver;
	float rightArmAngle = 0.f;
	float rightArmFinalAngle = 0.f;
	float rightArmRotationSpeed = 0.f;
	glm::vec2 pivotToCollider_ReferenceR;
	bool isCleaving = false;
	
	/* =============== General Data ===================== */
	bool isMirrored = false;
	glm::vec2 mousePos;
};