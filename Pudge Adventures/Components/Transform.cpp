
#include"Transform.h"

Transform::Transform() : Component(TRANSFORM){
	mPosX = mPosY = 0;
}

Transform::~Transform(){
	
}

void Transform::Update()
{

}

void Transform::Serialize(std::ifstream &inFile)
{
	inFile >> mPosX;
	inFile >> mPosY;
}
