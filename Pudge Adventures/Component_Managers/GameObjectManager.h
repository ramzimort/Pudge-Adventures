#pragma once

#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include <vector>
#include <set>
#include <iostream>

struct APtrComp
{
	bool operator()(const GameObject* lhs, const GameObject* rhs) const 
	{
		Transform* lpTR = static_cast<Transform*> (lhs->GetComponent(TRANSFORM));
		Transform* rpTR = static_cast<Transform*> (rhs->GetComponent(TRANSFORM));
		return (lpTR->zValue >= rpTR->zValue);
	}
};

class GameObjectManager {
	public:
		GameObjectManager();
		~GameObjectManager();
		void Update();
	public:
		std::set<GameObject*, APtrComp> mGameObjects;
};