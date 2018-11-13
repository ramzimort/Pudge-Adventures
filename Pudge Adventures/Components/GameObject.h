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