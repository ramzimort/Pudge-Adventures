
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Camera.h
Purpose: Component that handles camera locations (Must be attached to one object, will only use last loaded object for rendering if more are used)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);

public:
	glm::vec2 mCameraCenter;
	float rightBound;
	float upperBound;
	float CameraEnd;

private:
	void UpdateMousePosWorldSpace(glm::vec2& MouseScreenPosition);
};