#pragma once
#include <rapidjson/document.h>

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: LevelManager.h
Purpose: Handles loading next level when a win/lose condition is invoked (Button highlighting on menu screens is done here as well)
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

public:
	void Init(const std::string& LevelName);
	void Update();
	void Serialize(rapidjson::Document& objFile);

	void SetWinCondition();
	void SetLoseCondition();

private:
	std::string currentLevel;
	std::string nextLevelWin;
	std::string nextLevelLose;

	bool Flag_WinCondition;
	bool Flag_LoseCondition;

private:
	void WinCondition();
	void LoseCondition();
};