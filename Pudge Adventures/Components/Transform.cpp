
#include"Transform.h"

Transform::Transform() :	
	Component(TRANSFORM), 
	mPosition(0.0f,0.0f),
	zValue(0.0f),
	mScale(0.0f),
	mAngle(0.0f) { }

Transform::~Transform() { }

void Transform::Init()
{
}

void Transform::Update() { }

void Transform::Serialize(std::ifstream &inFile)
{
	inFile >> mPosition.x;
	inFile >> mPosition.y;
	inFile >> zValue;
	inFile >> mAngle;
	inFile >> mScale.x;
	inFile >> mScale.y;
}
