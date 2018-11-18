#pragma once

#include "Component.h"
#include "glm/vec2.hpp"


class Background : public Component
{
public:
	Background();
	~Background();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);

public:
	glm::vec2 mPos;
	float scrollingSpeed;
};