#pragma once

#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>

class Camera : public Component
{
public:
	Camera();
	~Camera();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
	void Serialize(rapidjson::Document& objectFile);

public:
	glm::vec2 mCameraCenter;
	float rightBound;
	float upperBound;
	float CameraEnd;

private:
	void UpdateMousePosWorldSpace(glm::vec2& MouseScreenPosition);
};