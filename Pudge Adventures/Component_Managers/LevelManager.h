#pragma once
#include <rapidjson/document.h>

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