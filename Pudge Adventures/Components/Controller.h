#pragma once

#include "Component.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Component_Managers\PhysicsManager.h"



class Controller : public Component{
public:
	Controller();
	~Controller();

	void Init();
	void Update();
	void HandleEvent(Event* pEvent);
};