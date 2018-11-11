#pragma once

#include "Component.h"
#include <glm/vec2.hpp>
#include <glm/glm.hpp>

class Transform : public Component{
public:
	Transform();
	~Transform();

	void Init();
	void Update();

	void Serialize(std::ifstream &inFile);
	void Serialize(rapidjson::Document& objectFile);

	glm::vec2				mPosition;			// Current position
	float					zValue;				// Object Depth
	glm::vec3				mScale;				// Current scale
	float					mAngle;				// Currenting value
};