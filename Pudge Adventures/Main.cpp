
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Main.cpp
Purpose: Main for testing assignment code
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#include <Windows.h>
#include <SDL2/SDL.h>

#include "Component_Managers/Input Manager.h"
#include "Component_Managers/FrameRateController.h"
#include "Component_Managers/Resource Manager.h"
#include "Component_Managers/GameObjectManager.h"
#include "Component_Managers/ObjectFactory.h"
#include "Component_Managers/GraphicsManager.h"
#include "Component_Managers/PhysicsManager.h"
#include "Component_Managers/CollisionManager.h"
#include "Component_Managers/EventManager.h"
#include "Component_Managers/LevelManager.h"
#include "Components/Component.h"
#include "Components/GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"
#include "Components/Body.h"
#include <iostream>
#include <glm/glm.hpp>



FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}

#pragma comment(lib, "legacy_stdio_definitions.lib")

Input_Manager* gpInputManager;
FrameRateController* gpFRC;
ResourceManager* gpResourceManager;
GameObjectManager* gpGameObjectManager;
ObjectFactory* gpObjectFactory;
GraphicsManager* gpGfxManager;
PhysicsManager* gpPhysicsManager;
CollisionManager* gpCollisionManager;
EventManager* gpEventManager;
LevelManager* gpLevelManager;


int main(int argc, char* args[])
{

	// Load Manager Start =================================================================================================================================================================================
	gpInputManager = new Input_Manager();			// Load Input Manager
	gpFRC = new FrameRateController(100);			// Load FrameRate Controller
	gpResourceManager = new ResourceManager();		// Load Resource Manager
	gpGameObjectManager = new GameObjectManager();	// Load Game Object Manager
	gpObjectFactory = new ObjectFactory();			// Load Object Factory
	gpGfxManager = new GraphicsManager();			// Load Graphics Manager
	gpPhysicsManager = new PhysicsManager();		// Load Physics Manager
	gpCollisionManager = new CollisionManager();	// Load Collision Manager
	gpEventManager = new EventManager();			// Load Events Manager
	gpLevelManager = new LevelManager();
	// Load Managers End	=================================================================================================================================================================================

	gpLevelManager->Init("Menu_Main");

	// Load Objects Start =================================================================================================================================================================================
	//std::string lvlPath = "Test";
	//gpObjectFactory->LoadLevel(lvlPath);
	// Load Objects End =================================================================================================================================================================================

	gpPhysicsManager->Init();

	// Game Loop Start =================================================================================================================================================================================
	while (!gpInputManager->isQuit())									
	{

		gpFRC->FrameStart();										// Frame Start
		// Manager Update Start =================================================================================================================================================================================
		gpInputManager->Update();
		gpPhysicsManager->Update(gpFRC->GetFrameTime());
		gpEventManager->Update();
		gpGameObjectManager->Update();
		gpGfxManager->Update();
		gpLevelManager->Update();
		// Manager Update End =================================================================================================================================================================================
		gpFRC->FrameEnd();											// Frame End
		//std::cout << "FPS: " << 1.0f/gpFRC->GetFrameTime() << std::endl;
	}
	// Game Loop End =================================================================================================================================================================================

	// Clear Manager Start =================================================================================================================================================================================
	delete gpFRC;							// Clear Frame Rate Controller
	delete gpInputManager;					// Clear Input Manager
	delete gpResourceManager;				// Clear Resource Manager
	delete gpGameObjectManager;				// Clear Game Object Manager
	delete gpObjectFactory;					// Clear Game Object Factory
	delete gpGfxManager;					// Clear Graphics Manager
	delete gpPhysicsManager;				// Clear Physics Manager
	delete gpCollisionManager;				// Clear Collision Manager
	delete gpEventManager;					// Clear Event Manager
	// Clear Manager End =================================================================================================================================================================================
	
	return 0;
}