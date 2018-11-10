
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
	for (auto go : mGameObjects) {
		go->Update();
	}
}
