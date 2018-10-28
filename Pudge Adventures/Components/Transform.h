#pragma once

#include "Component.h"

class Transform : public Component{
public:
	Transform();
	~Transform();

	void Update();

	void Serialize(std::ifstream &inFile);

	float mPosX;
	float mPosY;
};