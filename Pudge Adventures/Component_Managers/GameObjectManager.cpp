
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager() {

}

GameObjectManager::~GameObjectManager(){
	for (auto go : mGameObjects)
		delete go;
	mGameObjects.clear();
}

void GameObjectManager::Update()
{
	while (!toBeDeleted.empty())
	{
		GameObject* go = toBeDeleted.front();
		toBeDeleted.pop();

		mGameObjects.erase(go);
		delete go;
	}

	while (!toBeCreated.empty())
	{
		mGameObjects.insert(toBeCreated.front());
		toBeCreated.pop();
	}

	for (auto go : mGameObjects) 
		go->Update();
}

