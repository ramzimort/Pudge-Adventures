#include "ObjectFactory.h"
#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include <fstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>


extern GameObjectManager* gpGameObjectManager;

ObjectFactory::ObjectFactory()
{
}

ObjectFactory::~ObjectFactory()
{
}

void ObjectFactory::LoadLevel(std::string& pFileName) {

	std::ifstream inFile;
	inFile.open(pFileName);
	if (!inFile.is_open())
	{
		std::cout << "Could not open file" << pFileName << std::endl;
		return;
	}
	rapidjson::IStreamWrapper isw{ inFile };
	rapidjson::Document levelFile { };
	levelFile.ParseStream(isw);
	assert(levelFile.IsObject());
	std::string objectFileName;
	for (auto& ObjectName : levelFile.GetObject())
	{
		objectFileName = ObjectName.name.GetString();
		objectFileName = "Resources\\" + objectFileName + ".json";
		GameObject* pGameObject = LoadObject(objectFileName);
		// Add code for modifying instance positions


		if (pGameObject == nullptr)
		{
			std::cout << "Could not load object: " << objectFileName << std::endl;
			continue;
		}
		gpGameObjectManager->mGameObjects.insert(pGameObject);
	}
}

GameObject* ObjectFactory::LoadObject(std::string& pFileName) {
	std::ifstream inFile;
	inFile.open(pFileName);
	GameObject* pNewGameObject = nullptr;
	if (!inFile.is_open()) {
		std::cout << "Could not open file" << pFileName << std::endl;
		return pNewGameObject;
	}

	rapidjson::IStreamWrapper isw{ inFile };
	rapidjson::Document objectFile{ };
	objectFile.ParseStream(isw);
	assert(objectFile.IsObject());
	std::string componentName;
	

	pNewGameObject = new GameObject();
	for (auto& Components : objectFile.GetObject())
	{
		componentName = Components.name.GetString();
		Component* pNewComponent = nullptr;
		if ("Transform" == componentName)
		{
			pNewComponent = pNewGameObject->AddComponent(TRANSFORM);
			pNewComponent->Serialize(objectFile);
		}
		else if ("Sprite" == componentName)
		{
			pNewComponent = pNewGameObject->AddComponent(SPRITE);
			pNewComponent->Serialize(objectFile);
		}
		else if ("Controller" == componentName)
		{
			if(Components.value.GetBool())
				pNewComponent = pNewGameObject->AddComponent(CONTROLLER);
		}
		else if ("AI" == componentName)
		{
			pNewComponent = pNewGameObject->AddComponent(BOTAI);
			pNewComponent->Serialize(objectFile);
		}
		else if ("Body" == componentName)
		{
			pNewComponent = pNewGameObject->AddComponent(BODY);
			pNewComponent->Serialize(objectFile);
		}
	}
	inFile.close();
	return pNewGameObject;

}