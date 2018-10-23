
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Input Manager.h
Purpose: Input Manager header (provides check for if button is pressed, released, or triggered)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 10/18/2018
- End Header --------------------------------------------------------*/

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL_stdinc.h"

class Input_Manager
{
public: 
	Input_Manager();
	~Input_Manager();

	void Update();
	bool isPressed(unsigned int KeyScanCode);
	bool isTriggered(unsigned int KeyScanCode);
	bool isReleased(unsigned int KeyScanCode);

private:
	Uint8 mCurrentState[512];
	Uint8 mPreviousState[512];
};

#endif // !INPUT_MANAGER_H
