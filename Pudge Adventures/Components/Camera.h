#pragma once

#include "Component.h"
#include "GameObject.h"
#include <glm/glm.hpp>

class Camera : public Component
{
	public:
		Camera();
		~Camera();


	public:
		glm::vec2 mPos;
};