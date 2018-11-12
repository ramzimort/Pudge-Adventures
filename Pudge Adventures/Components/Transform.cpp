
#include"Transform.h"
#include "..\Events\RotateArm.h"
#include <iostream>

Transform::Transform() :	
	Component(TRANSFORM), 
	mPosition(0.0f,0.0f),
	zValue(0.0f),
	mScale(0.0f),
	mRotationCenter(0.0f),
	mAngle(0.0f) { }

Transform::~Transform() { }

void Transform::Init()
{
}

void Transform::Update() { }

void Transform::HandleEvent(Event* pEvent)
{
	if (pEvent->mType == ROTATE_ARM)
	{
		mpOwner;
		RotateArmEvent* RAE = static_cast<RotateArmEvent*>(pEvent);
		glm::vec2 PudgeCentertoMousePointer = RAE->pointerPos - mPosition;
		std::cout << PudgeCentertoMousePointer.x << ' ' << PudgeCentertoMousePointer.y << std::endl;
		mAngle = glm::degrees(atan2(PudgeCentertoMousePointer.y, PudgeCentertoMousePointer.x));
	}
}

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
		else if (componentValueName == "xRotationCenter")
			mRotationCenter.x = ComponentValues.value.GetFloat();
		else if (componentValueName == "yRotationCenter")
			mRotationCenter.y = ComponentValues.value.GetFloat();
	}
}
