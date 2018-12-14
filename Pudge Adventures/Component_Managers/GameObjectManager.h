#pragma once

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: GameObjectManager.h
Purpose: Stores list of all game objects. Sorts from nearest to farthest based on z-value (Positive scale)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include <vector>
#include <set>
#include <list>
#include <queue>
#include <iostream>

struct APtrComp
{
	bool operator()(const GameObject* lhs, const GameObject* rhs) const 
	{
		Transform* lpTR = static_cast<Transform*> (lhs->GetComponent(TRANSFORM));
		Transform* rpTR = static_cast<Transform*> (rhs->GetComponent(TRANSFORM));
		if (lpTR->zValue == rpTR->zValue)
			return lhs < rhs;
		else
			return (lpTR->zValue > rpTR->zValue);
	}
};

class GameObjectManager {
	public:
		GameObjectManager();
		~GameObjectManager();
		void Update();
	public:
		std::set<GameObject*, APtrComp> mGameObjects;			// Using a set to keep objects sorted from furthest to nearest (based on z-value)
		
		std::queue<GameObject*> toBeCreated;
		std::queue<GameObject*> toBeDeleted;					
};