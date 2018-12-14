
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Component.h
Purpose: Parent Class for all components
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <fstream>
#include <rapidjson/document.h>


enum COMPONENT_TYPE {
	CAMERA,
	TRANSFORM,
	SPRITE,
	BODY,
	ARMS,
	CONTROLLER,
	BACKGROUND,
	ATTRIBUTES,
	POWERUP,
	BOTAI,
	BOTAI2,
	BOTAI3
};

class GameObject;
class Event;

class Component {
public:
	Component(unsigned int Type);
	virtual ~Component() {}

	virtual void Init() = 0;
	virtual void Update() = 0;
	unsigned int getType();
	virtual void Serialize(rapidjson::Document& objFile) { }
	virtual void HandleEvent(Event* pEvent) { }

public:
	GameObject* mpOwner;

private:
	unsigned int mType;
};
