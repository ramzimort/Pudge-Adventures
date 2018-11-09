
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
#include "..\Components\TextureObject.h"

ResourceManager::ResourceManager() {
	
}

ResourceManager::~ResourceManager() {	
	for (auto &element : mTextures)
		delete element.second;

	mTextures.clear();
}

Texture* ResourceManager::LoadTexture(std::string& pFileName)
{
	Texture* pTexture = mTextures[pFileName];
	if (pTexture)
		return pTexture;
	pTexture = new Texture(pFileName);
	if (pTexture)
		mTextures[pFileName] = pTexture;
	return pTexture;
}