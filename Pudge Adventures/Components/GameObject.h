#pragma once

#include <vector>

class Component;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	void AddComponent(unsigned int Type);
	Component* GetComponent(unsigned int Type);

public:
	std::vector<Component*> mComponents;
};