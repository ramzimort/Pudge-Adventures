#pragma once
#define STB_IMAGE_IMPLEMENTATION

#include"Component.h"

#include "..\Include\SDL2\SDL_surface.h"


class Texture;

class Sprite : public Component {

public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(std::ifstream &inFile);

	SDL_Surface* mpSurface;
	
	Texture* mpTexture;
	int uCoord = 0;
	int vCoord = 0;
};