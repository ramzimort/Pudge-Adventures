
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Resource Manager.cpp
Purpose: Resource Manager implementation file
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/


#include "Resource Manager.h"
#include "..\Include\SDL2\SDL_surface.h"

ResourceManager::ResourceManager() {
	
}

ResourceManager::~ResourceManager() {
	for (auto &element : mSurfaces)
		SDL_FreeSurface(element.second);

	mSurfaces.clear();
}

SDL_Surface* ResourceManager::LoadSurface(const char* pFilePath) {

	// Check hash map
	SDL_Surface* pSurface = mSurfaces[pFilePath];

	// Already Loaded?
	if (pSurface)
		return pSurface;

	// Load it
	pSurface = SDL_LoadBMP(pFilePath);

	//Load successful? Add to hash map
	if (pSurface)
		mSurfaces[pFilePath] = pSurface;

	return pSurface;
}