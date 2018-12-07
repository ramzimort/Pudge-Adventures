
#define STB_IMAGE_IMPLEMENTATION

#include "Sprite.h"
#include "..\Component_Managers\Resource Manager.h"
#include "..\Component_Managers\FrameRateController.h"
#include <GLAD/glad.h>
#include <iostream>
#include <stb_image.h>
#include <iostream>

#undef GetObject


extern ResourceManager* gpResourceManager;
extern FrameRateController* gpFRC;

Texture::Texture(std::string& pFileName)
{
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// load and generate the texture
	int width, height, nrChannels;
	std::string pFilePath = "Textures\\" + pFileName;
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load(pFilePath.c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture: " << pFileName << std::endl;
	}
	stbi_image_free(data);
}
Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}
Sprite::Sprite() : 
	Component(SPRITE),
	mpTexture(nullptr)
{ }
Sprite::~Sprite() 
{ }
void Sprite::Init()
{ 
	currentTime = AnimationTime;
	currentAnimation = 0;
	enableAnimation = false;

}
void Sprite::Update()
{ 
	if (enableAnimation)
	{
		currentTime -= gpFRC->GetFrameTime();
		if (currentTime < 0.f)
		{
			IncrementAnimation();
			currentTime = AnimationTime;
		}
	}

	// Set Texture to current Animation Sprite
	mpTexture = SpriteAnimation[currentAnimation];
}

using namespace rapidjson;
void Sprite::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["Sprite"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "Animation")
		{
			for (unsigned int i = 0; i < ComponentValues.value.GetArray().Size(); ++i)
			{
				
				std::string imageName = ComponentValues.value.GetArray()[i].GetString();
				mpTexture = gpResourceManager->LoadTexture(imageName);
				SpriteAnimation.push_back(mpTexture);
			}
		}
		else if (componentValueName == "AnimationTime")
			AnimationTime = ComponentValues.value.GetFloat();
	}
}

void Sprite::SetAnimation(const unsigned int & ID)
{
	currentAnimation = ID;
	currentTime = AnimationTime;
}

void Sprite::ResetAnimation()
{
	currentAnimation = 0;
	currentTime = AnimationTime;
}

void Sprite::IncrementAnimation()
{
	currentAnimation++;
	if (currentAnimation >= SpriteAnimation.size())
		currentAnimation = 0;
	currentTime = AnimationTime;
}
