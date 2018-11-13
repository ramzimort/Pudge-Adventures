#pragma once

#include "Component.h"
#include <glm/glm.hpp>
#include <vector>

class Arms : public Component
{
	public:
		Arms();
		~Arms();

		void Init();
		void Update();
		void HandleEvent(Event* pEvent);

		void Serialize(rapidjson::Document& objectFile);

	public:
		GameObject* mpArms[2];
};