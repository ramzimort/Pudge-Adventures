#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class Transform : public Component{
public:
	Transform();
	~Transform();

	void Update();

	void Serialize(std::ifstream &inFile);

	glm::vec3				mPosition;			// Current position
	glm::vec3				mScale;				// Current scale
	float					mAngle;				// Currenting value
};