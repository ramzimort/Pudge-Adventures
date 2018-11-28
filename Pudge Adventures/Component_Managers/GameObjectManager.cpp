
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
	while (!toBeCreated.empty())
	{
		mGameObjects.insert(toBeCreated.front());
		toBeCreated.pop();
	}

	for (auto go : toBeDeleted)
	{
		mGameObjects.erase(go);
		delete go;
	}

	for (auto go : mGameObjects) 
		go->Update();

	toBeDeleted.clear();
}

