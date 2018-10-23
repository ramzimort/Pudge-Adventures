#pragma once

#include"GameObject.h"
#include<vector>

class GameObjectManager {
public:

	GameObjectManager();
	~GameObjectManager();

	std::vector<GameObject*> mGameObjects;
}