#pragma once

#include<string>

class Texture{
public:
	Texture(std::string& pFilePath);
	~Texture();

public:
	unsigned int textureID;
};