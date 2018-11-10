#pragma once

#include <fstream>


enum COMPONENT_TYPE {
	TRANSFORM,
	SPRITE,
	CONTROLLER,
	CAMERA,
	BODY,
	BOTAI

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

	virtual void Serialize(std::ifstream &inFile) {}
	virtual void HandleEvent(Event* pEvent) {}

public:
	GameObject* mpOwner;

private:
	unsigned int mType;
};
