/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input Manager.h
Purpose: Input Manager header (provides check for if button is pressed, released, or triggered)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#pragma once

#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_events.h>

class Input_Manager
{
public: 
	Input_Manager() ;
	~Input_Manager();

	void Update();
	bool isPressed(unsigned int KeyScanCode);
	bool isTriggered(unsigned int KeyScanCode);
	bool isReleased(unsigned int KeyScanCode);
	bool isMousePressed();
	int* PointerLocation();
	bool isQuit();


private:
	SDL_Event event;
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
	bool mIsMousePressed;
	int mousePosition[2];
	bool quit = { false };
};


