#pragma once

#include "Component.h"
#include <fstream>
#include <glm/glm.hpp>

class Shape;

class Body : public Component
{
public:
	Body();
	~Body();

	void Update();
	void Serialize(std::ifstream& inFile);
	void Initialize();
	void Integrate(float Gravity, float dt);

public:
	glm::vec2 mPos;
	glm::vec2 mPrevPos;
	glm::vec2 mVel;
	glm::vec2 mAcc;
	glm::vec2 mForce;
	float mMass, mInvMass;

	Shape* mpShape;
};