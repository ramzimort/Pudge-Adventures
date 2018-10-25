#pragma once

#include "Component.h"

class Controller : public Component{
public:
	Controller();
	~Controller();

	void Update();
};