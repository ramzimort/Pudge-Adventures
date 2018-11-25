#pragma once

#include "Component.h"

enum RuneType
{
	REGEN,
	HASTE,
	DD
};

class PowerUp : public Component
{
public:
	PowerUp();
	~PowerUp();

	void Init();
	void Update();
	void Serialize(rapidjson::Document& objFile);
	void HandleEvent(Event* pEvent);
public:
	RuneType mType;
};