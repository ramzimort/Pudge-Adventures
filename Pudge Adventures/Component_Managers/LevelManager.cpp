#include "LevelManager.h"
#include "ObjectFactory.h"
#include "GameObjectManager.h"
#include "EventManager.h"
#include "Input Manager.h"
#include "..\Components\Sprite.h"

extern ObjectFactory* gpObjectFactory;
extern GameObjectManager* gpGameObjectManager;
extern Input_Manager* gpInputManager;
extern EventManager* gpEventManager;

LevelManager::LevelManager()
{ }

LevelManager::~LevelManager()
{ }

void LevelManager::Init(const std::string& levelName)
{
	Flag_WinCondition = false;
	Flag_LoseCondition = false;
	gpObjectFactory->LoadLevel(levelName);
	currentLevel = levelName;
}

void LevelManager::Update()
{
	
	if (currentLevel == "Menu_Main")
	{
		GameObject* Menu_Object = *(gpGameObjectManager->mGameObjects.begin());
		int pointerX = gpInputManager->PointerLocation()[0];
		int pointerY = gpInputManager->PointerLocation()[1];
		
		if (pointerX > 120 && pointerX < 690 && pointerY > 350 && pointerY < 580)
		{
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->SetAnimation(1);
			if (gpInputManager->isMousePressed())
				WinCondition();
		}

		else if (pointerX > 140 && pointerX < 670 && pointerY > 90 && pointerY < 300)
		{
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->SetAnimation(2);
			if (gpInputManager->isMousePressed())
				LoseCondition();
			
		}
		else
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->ResetAnimation();
	}
	else if (currentLevel == "Menu_Controls")
	{
		GameObject* Menu_Object = *(gpGameObjectManager->mGameObjects.begin());
		int pointerX = gpInputManager->PointerLocation()[0];
		int pointerY = gpInputManager->PointerLocation()[1];
		if (pointerX > 1160 && pointerX < 1260  && pointerY > 650 && pointerY < 680)
		{
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->SetAnimation(1);
			if (gpInputManager->isMousePressed())
				WinCondition();
		}

		else if (pointerX > 20 && pointerX < 120 && pointerY > 650 && pointerY < 680)
		{
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->SetAnimation(2);
			if (gpInputManager->isMousePressed())
				LoseCondition();

		}
		else
			static_cast<Sprite*>(Menu_Object->GetComponent(SPRITE))->ResetAnimation();
	}
	else if (currentLevel == "Lost")
	{
		if (gpInputManager->isMousePressed())
			WinCondition();
	}
	else if (currentLevel == "Won")
	{
		if (gpInputManager->isMousePressed())
			WinCondition();
	}
	else
	{
		if (Flag_WinCondition)
			WinCondition();
		else if (Flag_LoseCondition)
			LoseCondition();
	}
}

void LevelManager::WinCondition()
{
	Flag_WinCondition = false;
	currentLevel = nextLevelWin;
	delete gpGameObjectManager;
	gpGameObjectManager = new GameObjectManager();
	delete gpEventManager;
	gpEventManager = new EventManager();
	gpObjectFactory->LoadLevel(nextLevelWin);
	
}

void LevelManager::LoseCondition()
{
	Flag_LoseCondition = false;
	currentLevel = nextLevelLose;
	delete gpGameObjectManager;
	gpGameObjectManager = new GameObjectManager();
	delete gpEventManager;
	gpEventManager = new EventManager();

	gpObjectFactory->LoadLevel(nextLevelLose);
	
}

void LevelManager::Serialize(rapidjson::Document & objFile)
{
	if (objFile.HasMember("WinLevel"))
		nextLevelWin = objFile["WinLevel"].GetString();
	if (objFile.HasMember("LoseLevel"))
		nextLevelLose = objFile["LoseLevel"].GetString();
}

void LevelManager::SetWinCondition()
{
	Flag_WinCondition = true;
}

void LevelManager::SetLoseCondition()
{
	Flag_LoseCondition = true;
}
