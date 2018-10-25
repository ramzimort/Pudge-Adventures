#pragma once

#include "..\Components\GameObject.h"
#include <vector>

class GameObjectManager {
public:
	GameObjectManager();
	~GameObjectManager();

	std::vector<GameObject*> mGameObjects;
};