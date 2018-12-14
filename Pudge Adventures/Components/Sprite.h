
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Sprite.h
Purpose: Adds texture to object. (If object has animations, stores all animation sprites which can be manipulated manually or automatically (time-based))
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include "Component.h"
#include <vector>

class Texture {
public:
	Texture(std::string& pFilePath);
	~Texture();

public:
	unsigned int textureID;
};

class Sprite : public Component {

public:
	Sprite();
	~Sprite();

	void Init();
	void Update();

	void Serialize(rapidjson::Document& objectFile);

	bool enableAnimation;
	float currentTime;
	float AnimationTime;
	
	Texture* mpTexture;
	float uv[2];

public:
	void SetAnimation(const unsigned int& ID);
	void ResetAnimation();
	void IncrementAnimation();


private:
	unsigned int currentAnimation;
	std::vector<Texture*> SpriteAnimation;
};