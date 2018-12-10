#pragma once

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