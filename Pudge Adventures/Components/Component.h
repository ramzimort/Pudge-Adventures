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
	BOTAI,
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
	virtual void Serialize(rapidjson::Document& objFile) {}
	virtual void HandleEvent(Event* pEvent) {}

public:
	GameObject* mpOwner;

private:
	unsigned int mType;
};
