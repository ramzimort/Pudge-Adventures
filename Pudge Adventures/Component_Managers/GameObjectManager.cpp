
#include "GameObjectManager.h"
#include "LevelManager.h"

extern LevelManager* gpLevelManager;

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
		// If you die -> Lose Condition
		if (go->HasComponent(CONTROLLER))
			gpLevelManager->SetLoseCondition();
		// If you kill the boss -> Win Condition
		if (go->HasComponent(BOTAI3))
			gpLevelManager->SetWinCondition();
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

