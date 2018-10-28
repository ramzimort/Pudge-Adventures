

#include "Sprite.h"
#include "..\Component_Managers\Resource Manager.h"

extern ResourceManager* gpResourceManager;

Sprite::Sprite() : Component(SPRITE) {
	mpSurface = NULL;
}

Sprite::~Sprite() {

}

void Sprite::Update()
{
}

void Sprite::Serialize(std::ifstream &inFile)
{
	std::string imageName = "";
	
	std::string fullpath = ".\\Resources\\";
	
	inFile >> imageName;

	fullpath += imageName;

	mpSurface = gpResourceManager->LoadSurface(fullpath.c_str());

}
