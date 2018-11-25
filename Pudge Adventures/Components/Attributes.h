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

private:
	void UpdateHealthBar();
	void UpdateHasteBar();
	void UpdateDDBar();
};