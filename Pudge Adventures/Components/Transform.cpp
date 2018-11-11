
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

void Transform::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["Transform"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "X")
			mPosition.x = ComponentValues.value.GetFloat();
		else if(componentValueName == "Y")
			mPosition.y = ComponentValues.value.GetFloat();
		else if (componentValueName == "Z")
			zValue = ComponentValues.value.GetFloat();
		else if (componentValueName == "Angle")
			mAngle = ComponentValues.value.GetFloat();
		else if (componentValueName == "xScale")
			mScale.x = ComponentValues.value.GetFloat();
		else if (componentValueName == "yScale")
			mScale.y = ComponentValues.value.GetFloat();
	}
}
