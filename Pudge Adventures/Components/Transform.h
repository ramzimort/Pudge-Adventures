
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Transform.h
Purpose: Contains render information. Used by graphicsmanager to render the object to screen
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class Transform : public Component{
public:
	Transform();
	~Transform();
	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);
	
public:
	glm::vec2				mPosition;			// Current position
	float					zValue;				// Object Depth
	glm::vec2				mScale;				// Current scale
	glm::vec2				mRotationCenter;	// Center of Rotation
	float					mAngle;				// Currenting value
	bool					isTiled;			// Tiled Objects Drawing

private:
	void RotateBody(float deltaAngle);
};