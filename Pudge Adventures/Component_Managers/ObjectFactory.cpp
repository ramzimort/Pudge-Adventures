#include "ObjectFactory.h"
#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include <fstream>
#include <iostream>
#include <rapidjson/istreamwrapper.h>
#include <glm/glm.hpp>

extern GameObjectManager* gpGameObjectManager;

ObjectFactory::ObjectFactory()
{ }
ObjectFactory::~ObjectFactory()
{ }
void ObjectFactory::LoadLevel(std::string& pFileName) {

	std::ifstream inFile;
	std::string pFilePath = "Resources\\Levels\\" + pFileName + ".json";
	inFile.open(pFilePath);
	if (!inFile.is_open())
	{
		std::cout << "Could not open file" << pFilePath << std::endl;
		return;
	}
	rapidjson::IStreamWrapper isw{ inFile };
	rapidjson::Document levelFile { };
	levelFile.ParseStream(isw);
	assert(levelFile.IsObject());
	for (auto& Data : levelFile.GetObject())
	{
		std::string DataName = Data.name.GetString();
		// Add code for other level related information (SCR_SIZE, MUSIC, Color)


		////////////////////////////////////////////////////////////////////////
		
		if (DataName == "Objects" && Data.value.IsArray())
		{

			auto listOfObjects = Data.value.GetArray();
			for (unsigned int i = 0; i < listOfObjects.Size(); i++)
			{
				auto ObjectInstance = listOfObjects[i].GetObject();
				std::string PrefabName = ObjectInstance["Name"].GetString();
				GameObject* pGameObject = LoadObject(PrefabName);
				////////////////////////////////////////
				if (pGameObject == nullptr)
				{
					std::cout << "Could not load object: " << PrefabName << std::endl;
					continue;
				}
				/* Add code for modifying instance positions*/
				Transform* pTr = static_cast<Transform*>(pGameObject->GetComponent(TRANSFORM));
				if (pTr != nullptr)
				{
					for (auto& Override : ObjectInstance)
					{
						std::string ArchetypeName = Override.name.GetString();
						if (ArchetypeName == "PosX")
							pTr->mPosition.x = Override.value.GetFloat();
						else if (ArchetypeName == "PosY")
							pTr->mPosition.y = Override.value.GetFloat();
						else if (ArchetypeName == "Z")
							pTr->zValue = Override.value.GetFloat();
						else if (ArchetypeName == "xScale")
							pTr->mScale.x = Override.value.GetFloat();
						else if (ArchetypeName == "yScale")
							pTr->mScale.y = Override.value.GetFloat();
					}
				}
				pGameObject->Init();
			}
		}
	}
}
GameObject* ObjectFactory::LoadObject(std::string& pFileName) {
	std::ifstream inFile;
	std::string pFilePath = "Resources\\Prefabs\\" + pFileName + ".json";
	inFile.open(pFilePath);
	GameObject* pNewGameObject = nullptr;
	if (!inFile.is_open()) {
		std::cout << "Could not open file" << pFilePath << std::endl;
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
		LoadComponent(componentName, pNewGameObject, objectFile);			
	}
	gpGameObjectManager->mGameObjects.insert(pNewGameObject);
	inFile.close();
	return pNewGameObject;

}
Component * ObjectFactory::LoadComponent(std::string& componentName, GameObject* pNewGameObject, rapidjson::Document& objectFile)
{
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
		pNewComponent = pNewGameObject->AddComponent(CONTROLLER);
		pNewComponent->Serialize(objectFile);
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
	else if ("Arms" == componentName)
	{
		pNewComponent = pNewGameObject->AddComponent(ARMS);
		pNewComponent->Serialize(objectFile);
	}
	else if ("Camera" == componentName)
	{
		pNewComponent = pNewGameObject->AddComponent(CAMERA);
		pNewComponent->Serialize(objectFile);
	}
	else if ("Background" == componentName)
	{
		pNewComponent = pNewGameObject->AddComponent(BACKGROUND);
		pNewComponent->Serialize(objectFile);
	}
	else if ("Attributes" == componentName)
	{
		pNewComponent = pNewGameObject->AddComponent(ATTRIBUTES);
		pNewComponent->Serialize(objectFile);
	}
	else if ("PowerUp" == componentName)
	{
		pNewComponent = pNewGameObject->AddComponent(POWERUP);
		pNewComponent->Serialize(objectFile);
	}
	return pNewComponent;
}
