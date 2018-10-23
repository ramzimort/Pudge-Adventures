#pragma once

class SDL_Surface;

class Sprite {

public:
	Sprite();
	~Sprite();

	void Update();

	SDL_Surface* mpSurface;
};