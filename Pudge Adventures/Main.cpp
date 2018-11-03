


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
#include "Include/SDL2/SDL.h"
#include "stdio.h"
#include "Component_Managers/Input Manager.h"
#include "Component_Managers/FrameRateController.h"
#include "Component_Managers/Resource Manager.h"
#include "Component_Managers/GameObjectManager.h"
#include "Component_Managers/ObjectFactory.h"
#include "Component_Managers/GraphicsManager.h"
#include "Component_Managers/PhysicsManager.h"
#include "Component_Managers/CollisionManager.h"

#include "Components/Component.h"
#include "Components/GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"
#include "Components/Body.h"

#include <iostream>
#include <stdio.h>



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
//PhysicsManager* gpPhysicsManager;
//CollisionManager* gpCollisionManager;


int main(int argc, char* args[])
{

	// Load Manager Start =================================================================================================================================================================================
	
	SDL_Window *pWindow;										// Window object pointer
	SDL_Surface* pWindowSurface;								// Window surface object
	SDL_Surface* pImage = NULL;									// Image pointer, loaded from resource manager

	SDL_Rect destinationRectangle;								// Object Rectangle 
	int posX = 0,
		posY = 0,
		moveSpeed = 1;											// Movement/msec

	gpInputManager = new Input_Manager();						// Load Input Manager
	gpFRC = new FrameRateController(100);						// Load FrameRate Controller
	gpResourceManager = new ResourceManager();					// Load Resource Manager
	gpGameObjectManager = new GameObjectManager();				// Load Game Object Manager
	gpObjectFactory = new ObjectFactory();						// Load Object Factory
	gpGfxManager = new GraphicsManager();						// Load Graphics Manager
	//gpPhysicsManager = new PhysicsManager();
	//gpCollisionManager = new CollisionManager();

	//// Load Managers End	=================================================================================================================================================================================

	//// Load Objects Start =================================================================================================================================================================================
	//
	std::string lvlPath = "Resources\\Level1.txt";
	gpObjectFactory->LoadLevel(lvlPath);

	//// Load Objects End =================================================================================================================================================================================
	
	
	while (!gpInputManager->isQuit())									// Game loop
	{

		gpFRC->FrameStart();										// Frame Start
		//std::cout << "Frame Time: " << gpFRC->GetFrameTime() << "ms" << std::endl;


		gpInputManager->Update();
		gpGfxManager->clearColor();


		//gpPhysicsManager->Update(gpFRC->GetFrameTime());

		// Update all game objects
		for (auto go : gpGameObjectManager->mGameObjects) {
			go->Update();
			if (go->GetComponent(SPRITE) != nullptr && go->GetComponent(TRANSFORM) != nullptr)
			{
				gpGfxManager->Draw(go);
			}
		}
		
		gpGfxManager->refreshWindow();
		
		gpFRC->FrameEnd();											// Frame End
	}

	delete gpFRC;							// Clear Frame Rate Controller
	delete gpInputManager;					// Clear Input Manager
	delete gpResourceManager;				// Clear Resource Manager
	delete gpGameObjectManager;				// Clear Game Object Manager
	delete gpObjectFactory;					// Clear Game Object Factory
	delete gpGfxManager;					// Clear Graphics Manager
	//delete gpPhysicsManager;
	//delete gpCollisionManager;

	//SDL_FreeSurface(pWindowSurface);		// Clear Window Surface
	//SDL_DestroyWindow(pWindow);				// Close and destroy the window

	SDL_Quit();								// Quit SDL subsystems	
	return 0;
}