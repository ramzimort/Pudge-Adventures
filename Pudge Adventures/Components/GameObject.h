#pragma once

#include <vector>
class Component;

class GameObject {
public:
	GameObject() {};
	~GameObject();

	void Update();
	void test123() {};
	void AddComponent(unsigned int Type);
	Component* GetComponent(unsigned int Type);

public:
	std::vector<Component*> mComponents;
};