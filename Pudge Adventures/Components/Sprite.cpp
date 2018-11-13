
#define STB_IMAGE_IMPLEMENTATION
#include "Sprite.h"
#include <GLAD/glad.h>
#include <iostream>
#include <stb_image.h>
#include "..\Component_Managers\Resource Manager.h"

extern ResourceManager* gpResourceManager;

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
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
}

Texture::~Texture()
{
	glDeleteTextures(1, &textureID);
}


Sprite::Sprite() : Component(SPRITE) {
	mpTexture = nullptr;
}

Sprite::~Sprite() 
{
}

void Sprite::Init()
{
}

void Sprite::Update()
{
}

void Sprite::Serialize(std::ifstream &inFile)
{
	std::string imageName = "";
	inFile >> imageName;
	mpTexture = gpResourceManager->LoadTexture(imageName);
}

void Sprite::Serialize(rapidjson::Document& objectFile)
{
	std::string imageName = objectFile["Sprite"].GetString();
	mpTexture = gpResourceManager->LoadTexture(imageName);
}
