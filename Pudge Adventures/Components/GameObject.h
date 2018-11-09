#pragma once

#include <vector>
class Component;

class GameObject {
public:
	GameObject();
	~GameObject();

	void Update();
	Component* AddComponent(unsigned int Type);
	Component* GetComponent(unsigned int Type) const;

public:
	std::vector<Component*> mComponents;
};