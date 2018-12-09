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
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);
	
public:
	glm::vec2				mPosition;			// Current position
	float					zValue;				// Object Depth
	glm::vec2				mScale;				// Current scale
	glm::vec2				mRotationCenter;	// Center of Rotation
	float					mAngle;				// Currenting value
	bool					isTiled;			// Tiled Objects Drawing

private:
	void RotateBody(float deltaAngle);
};