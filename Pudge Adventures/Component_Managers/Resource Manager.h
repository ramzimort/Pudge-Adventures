
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ResourceManager.h
Purpose: Resource Manager header (uses an unordered map to store textures)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <string>
#include <unordered_map>

struct SDL_Surface;
class Texture;

class ResourceManager {
public:
	ResourceManager();
	~ResourceManager();

	Texture* LoadTexture(std::string& pFilePath);

private:
	std::unordered_map<std::string, Texture*> mTextures;
};


