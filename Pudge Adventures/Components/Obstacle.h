#pragma once

#include "Component.h"

class Obstacle : public Component
{
public:
	Obstacle();
	~Obstacle();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);

	void Serialize(rapidjson::Document& objectFile);
};