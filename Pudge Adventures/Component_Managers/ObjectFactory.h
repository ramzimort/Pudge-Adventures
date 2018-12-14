#pragma once

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: ObjectFactory.h
Purpose: Handles loading objects from .json files to objectmanager. 
Was initially made for .txt then updated to .json
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

#include <string>
#include <rapidjson/document.h>

class GameObject;
class Component;

class ObjectFactory {
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadLevel(const std::string& pFileName);
	GameObject* LoadObject(const std::string& pFileName);

private:
	Component* LoadComponent(std::string& componentName, GameObject* pNewGameObject, rapidjson::Document& objectFile);
	void OverrideArchetype(GameObject* pGameObject, rapidjson::Value::Object &instance);
	void Repeat(GameObject* pGameObject, rapidjson::Value::Object &instance, std::string& PrefabName);
};