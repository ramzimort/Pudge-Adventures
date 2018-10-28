#include "ObjectFactory.h"

#include "..\Components\GameObject.h"
#include "..\Components\Transform.h"
#include "GameObjectManager.h"
#include <fstream>
#include <iostream>


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
	
	if (inFile.is_open()) {
		std::string objectFileName;

		while (!inFile.eof()) {
			objectFileName = "";
			inFile >> objectFileName;
			objectFileName = ".\\Resources\\" + objectFileName;
			GameObject* pGameObject = LoadObject(objectFileName);
			if (pGameObject == nullptr) {
				std::cout << "Could not load object: " << objectFileName << std::endl;
				continue;
			}

			Transform* pTr = static_cast<Transform*> (pGameObject->GetComponent(TRANSFORM));
			pTr->Serialize(inFile);
		}

		inFile.close();
	}
	else
		std::cout << "File: " << pFileName << " could not be opened" << std::endl;

}

GameObject* ObjectFactory::LoadObject(std::string& pFileName) {

	
	std::ifstream inFile;
	inFile.open(pFileName);
	GameObject* pNewGameObject = nullptr;

	if (inFile.is_open()) {
		pNewGameObject = new GameObject();
		std::string compononentName;

		while (!inFile.eof()) {
			inFile >> compononentName;
			Component* pNewComponent = nullptr;
			if ("Transform" == compononentName) {
				pNewComponent = pNewGameObject->AddComponent(TRANSFORM);
				pNewComponent->Serialize(inFile);
			}
			else if ("Sprite" == compononentName) {
				pNewComponent = pNewGameObject->AddComponent(SPRITE);
				pNewComponent->Serialize(inFile);
			}
			else if ("Controller" == compononentName) {
				pNewComponent = pNewGameObject->AddComponent(CONTROLLER);
			}
			gpGameObjectManager->mGameObjects.push_back(pNewGameObject);
		}
		inFile.close();
	}
	else
		std::cout << "File: " << pFileName << " could not be opened" << std::endl;

	return pNewGameObject;

}