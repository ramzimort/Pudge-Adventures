#pragma once

#pragma once


#include <GLAD/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <string>

class WindowManager
{
	WindowManager();
	virtual ~WindowManager();


protected:
	SDL_Window *pWindow;										// Window object pointer

	Uint32 SCR_WIDTH = 800;
	Uint32 SCR_HEIGHT = 600;

	bool errorFlag =  false;
	std::string errorString =  "";
};