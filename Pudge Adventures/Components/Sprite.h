#pragma once

#include"Component.h"
#include "..\Include\SDL2\SDL_surface.h"




class Sprite : public Component {

public:
	Sprite();
	~Sprite();

	void Update();

	void Serialize(std::ifstream &inFile);

	SDL_Surface* mpSurface;
};