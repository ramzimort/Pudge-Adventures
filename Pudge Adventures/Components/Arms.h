
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Arms.h
Purpose: Component that creates and handles any movement of pudges attachments (Hook, Cleaver, Left Arm, Right Arm, Hook Chain) (uses an unordered map to store textures)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

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
	GameObject* chain;
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