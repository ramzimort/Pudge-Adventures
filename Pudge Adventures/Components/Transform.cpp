
#include"Transform.h"

Transform::Transform() :	Component(TRANSFORM), 
							mPosition(0.0f,0.0f,0.0f), 
							mScale(0.0f),
							mAngle(0.0f)
{
	mPosition.x = 0;
	mPosition.y = 0;
}

Transform::~Transform(){
	
}

void Transform::Update()
{

}

void Transform::Serialize(std::ifstream &inFile)
{
	inFile >> mPosition.x;
	inFile >> mPosition.y;
	inFile >> mPosition.z;
	inFile >> mAngle;
	inFile >> mScale.x;
	inFile >> mScale.y;
}
