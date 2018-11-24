#pragma once

#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include <vector>
#include <set>
#include <list>
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
		std::set<GameObject*, APtrComp> mGameObjects;		// Using a set to keep objects sorted from furthest to nearest (based on z-value)
		std::set<GameObject*> toBeDeleted;					// Using a set to prevent duplicate GameObjects as these will be destroyed at the end of every frame
};