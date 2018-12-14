
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Attributes.h
Purpose: Component that deals with damage and hp (gameplay related attributes)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/


#pragma once

#define STB_IMAGE_IMPLEMENTATION
#include "Component.h"

class Texture;

class Attributes : public Component
{
public:
	Attributes();
	~Attributes();

	void Init();
	void Update();
	void Serialize(rapidjson::Document& objFile);
	void HandleEvent(Event* pEvent);

public:
	float maxHealth;
	float currentHealth;
	Texture* healthBar;

	float Damage;


	float RuneEffectTime;
	
	bool Regen;
	
	bool Haste;
	float HasteTimer;
	Texture* hasteBar;
	
	bool DD;
	float DDTimer;
	Texture* DDBar;

	GameObject* BloodSplatter;
	float BloodSplatterTimer;
	float BloodSplatterTime;

private:
	void UpdateHealthBar();
	void UpdateHasteBar();
	void UpdateDDBar();
	void CreateBloodSplatter();
};