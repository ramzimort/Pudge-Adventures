
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input Manager.cpp
Purpose: Input Manager implementation file
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#include "Input Manager.h"
#include <SDL2\SDL_keyboard.h>
#include <iostream>
#include "GraphicsManager.h"

extern GraphicsManager* gpGfxManager;


Input_Manager::Input_Manager() {
	SDL_memset(mCurrentState, 0, 512 * sizeof(Uint8));
	SDL_memset(mPreviousState, 0, 512 * sizeof(Uint8));
}

Input_Manager::~Input_Manager() {


}

void Input_Manager::Update() 
{
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT)
			quit = true;
		if (event.type == SDL_MOUSEBUTTONDOWN)
			mIsMousePressed = true;
		else
			mIsMousePressed = false;
	}
	int numberOffFetchedKeys = 0;
	
	const Uint8* pCurrentKeyStates = SDL_GetKeyboardState(&numberOffFetchedKeys);
	if (numberOffFetchedKeys > 512)
		numberOffFetchedKeys = 512;
	SDL_memcpy(mPreviousState, mCurrentState, 512*sizeof(Uint8));
	SDL_memcpy(mCurrentState, pCurrentKeyStates, numberOffFetchedKeys * sizeof(Uint8));
	SDL_GetMouseState(mousePosition, mousePosition+1);
	mousePosition[1] = -1 * mousePosition[1] + gpGfxManager->getWindowHeight();
}



bool Input_Manager::isPressed(unsigned int KeyScanCode) {
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::isTriggered(unsigned int KeyScanCode) {
	if (KeyScanCode >= 512)
		return false;

	if (mCurrentState[KeyScanCode] && !mPreviousState[KeyScanCode])
		return true;

	return false;
}

bool Input_Manager::isReleased(unsigned int KeyScanCode) {
	if (KeyScanCode >= 512)
		return false;

	if (!mCurrentState[KeyScanCode] && mPreviousState[KeyScanCode])
		return true;

	return false;
}

int* Input_Manager::PointerLocation()
{
	return mousePosition;
}

bool Input_Manager::isMousePressed()
{
	return mIsMousePressed;
}

bool Input_Manager::isQuit()
{
	return quit;
}
