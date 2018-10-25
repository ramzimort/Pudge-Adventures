
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Resource Manager.h
Purpose: Resource Manager header (uses an unordered map to store surfaces)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <string>
#include<unordered_map>

struct SDL_Surface;

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	SDL_Surface* LoadSurface(const char* pFilePath);

private:
	std::unordered_map<std::string, SDL_Surface*> mSurfaces;
};

