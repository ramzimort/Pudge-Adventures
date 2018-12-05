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

public:
	void SetAnimation(const unsigned int& ID);
	void ResetAnimation();
	void IncrementAnimation();


private:
	unsigned int currentAnimation;
	std::vector<Texture*> SpriteAnimation;
};