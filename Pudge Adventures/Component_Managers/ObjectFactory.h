#pragma once

#include <string>
#include <rapidjson/document.h>

class GameObject;
class Component;

class ObjectFactory {
public:
	ObjectFactory();
	~ObjectFactory();

	void LoadLevel(std::string& pFileName);
	GameObject* LoadObject(std::string& pFileName);

private:
	Component* LoadComponent(std::string& componentName, GameObject* pNewGameObject, rapidjson::Document& objectFile);
};