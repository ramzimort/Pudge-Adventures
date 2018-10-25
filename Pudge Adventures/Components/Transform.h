#pragma once

#include "Component.h"

class Transform : public Component{
public:
	Transform();
	~Transform();

	void Update();

	float mPosX;
	float mPosY;
};