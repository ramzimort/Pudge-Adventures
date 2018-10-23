#pragma once

enum COMPONENT_TYPE {
	TRANSFORM,
	SPRITE,
	CONTROLLER
};

class GameObject;

class Component {
public:
	Component(unsigned int Type);
	virtual ~Component() {}

	virtual void Update() = 0;
	unsigned int getType() { return mType; }

public:
	GameObject* mpOwner;


private:


private:
	unsigned int mType;
};
