
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Controller.h
Purpose: Component that handles button presses and applies them to object
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

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

public:
	bool moveEnable;
};