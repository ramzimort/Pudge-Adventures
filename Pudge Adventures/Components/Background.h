
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Background.h
Purpose: Component that handles parallax scrolling background objects
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/


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