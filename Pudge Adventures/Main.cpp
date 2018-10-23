


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
#include "stdio.h"
#include "Component_Managers/Input Manager.h"
#include "Component_Managers/FrameRateController.h"
#include "Component_Managers/Resource Manager.h"
#include "Component_Managers/GameObjectManager.h"
#include "Components/GameObject.h"
#include "Components/Sprite.h"
#include "Components/Transform.h"
#include "Components/Controller.h"

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

int main(int argc, char* args[])
{

	/* Initialization */
	SDL_Window *pWindow;										// Window object pointer
	SDL_Surface* pWindowSurface;								// Window surface object
	SDL_Surface* pImage = NULL;									// Image pointer, loaded from resource manager

	SDL_Rect destinationRectangle;								// Object Rectangle 
	int posX = 0,
		posY = 0,
		moveSpeed = 1;											// Movement/msec

	gpInputManager = new Input_Manager();						// Load Input Manager
	gpFRC = new FrameRateController(100);						// Load FrameRateController
	gpResourceManager = new ResourceManager();					// Load Resource Manager
	gpGameObjectManager = new GameObjectManager();				// Load GameObjectManager

	if (AllocConsole())
	{
		FILE* file;

		freopen_s(&file, "CONOUT$", "wt", stdout);
		freopen_s(&file, "CONOUT$", "wt", stderr);
		freopen_s(&file, "CONOUT$", "wt", stdin);

		SetConsoleTitle(L"SDL 2.0 Test");
	}

	int error = 0;												// Set error code to 0
	bool appIsRunning = true;									// Set app running to true

	if ((error = SDL_Init(SDL_INIT_VIDEO)) < 0)				// Initialize SDL
	{
		printf("Couldn't initialize SDL, error %i\n", error);
		system("Pause");
		return 1;
	}


	pWindow = SDL_CreateWindow("SDL2 window",					// window title
		SDL_WINDOWPOS_UNDEFINED,								// initial x position
		SDL_WINDOWPOS_UNDEFINED,								// initial y position
		800,													// width, in pixels
		600,													// height, in pixels
		SDL_WINDOW_SHOWN);


	if (NULL == pWindow)										// Check that the window was successfully made
	{

		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	pWindowSurface = SDL_GetWindowSurface(pWindow);				// Get Window Surface

	// Refresh the window
	SDL_UpdateWindowSurface(pWindow);							// Initialize Surface

	// Create Game Object 1
	{
		GameObject* pObject1 = new GameObject();
		//pObject1->mpTransform = new Transform();
		//pObject1->mpTransform->mPosX = 200.f;
		//pObject1->mpTransform->mPosY = 200.f;

		pObject1->AddComponent(TRANSFORM);
		Transform* pTr = static_cast<Transform*>(pObject1->GetComponent(TRANSFORM));

		pObject1->mpSprite = new Sprite();
		pObject1->mpSprite->mpSurface = pResourceManager->LoadSurface("..\\Resources\\Happy.bmp");

		pGameObjectManager->mGameObjects.push_back(pObject1);

		pObject1->mpController = new Controller();

	}


	while (true == appIsRunning)									// Game loop
	{

		gpFRC->FrameStart();										// Frame Start
		printf("Frame Time: %d ms\n", gpFRC->GetFrameTime());
		SDL_FillRect(pWindowSurface, NULL, 0x000000);
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				appIsRunning = false;
			}

		}

		gpInputManager->Update();

		for (auto go : gpGameObjectManager->mGameObjects) {
			if (go->mpSprite != nullptr && go->mpTransform != nullptr) {
				// Update object positions here, and update surface
				SDL_Rect destinationRect;
				destinationRect.x = (int)go->mpTransform->mPosX;
				destinationRect.y = (int)go->mpTransform->mPosY;
				SDL_BlitSurface(go->mpSprite->mpSurface, NULL, pWindowSurface, &destinationRectangle);
				SDL_UpdateWindowSurface(pWindow);							// Update object and window


			}
		}


		destinationRectangle.x = posX;
		destinationRectangle.y = posY;
		SDL_BlitSurface(pImage, NULL, pWindowSurface, &destinationRectangle);
		SDL_UpdateWindowSurface(pWindow);							// Update object and window

		gpFRC->FrameEnd();											// Frame End
	}

	delete gpFRC;							// Clear Frame Rate Controller
	delete gpInputManager;					// Clear Input Manager
	delete gpResourceManager;				// Clear Resource Manager
	delete gpGameObjectManager;				// Clear Game Object Manager

	SDL_FreeSurface(pWindowSurface);		// Clear Window Surface
	SDL_DestroyWindow(pWindow);				// Close and destroy the window

	SDL_Quit();								// Quit SDL subsystems	
	return 0;
}