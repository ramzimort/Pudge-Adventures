
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObject.h
Purpose: Stores list of components. Represents any object in the game
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <vector>
class Component;
class Event;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Init();
	void Update();
	Component* AddComponent(unsigned int Type);
	Component* GetComponent(unsigned int Type) const;
	bool HasComponent(unsigned int Type) const;
	void HandleEvent(Event* pEvent);

public:
	std::vector<Component*> mComponents;
};