
#include "Transform.h"
#include "GameObject.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\RotateArmTowardPointer.h"
#include "..\Events\UpdatePosition.h"

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
	InitializeBodyEvent InitializeBody;
	InitializeBody.InitialPosition = mPosition;
	mpOwner->HandleEvent(&InitializeBody);
}

void Transform::Update() { }

void Transform::HandleEvent(Event* pEvent)
{
	switch(pEvent->mType)
	{
	case(UPDATE_POSITION):
		mPosition = static_cast<UpdatePositionEvent*>(pEvent)->newPosition;
		break;
	case(ROTATE_ARM_TOWARD_POINTER):
		RotateArmTowardPointerEvent* RATPe = static_cast<RotateArmTowardPointerEvent*>(pEvent);
		glm::vec2 relativeArmPos = 
			mPosition 
			- RATPe->cameraCenter 
			+ glm::vec2((float)RATPe->SCR_WIDTH / 2.f, (float)RATPe->SCR_HEIGHT / 2.f);
		glm::vec2 PudgeCentertoMousePointer = 
			RATPe->pointerPos
			- relativeArmPos
			- glm::vec2(mRotationCenter.x*mScale.x, mRotationCenter.y*mScale.y); //Remove rotation center offset
		mAngle = 90.0f + glm::degrees(atan2(PudgeCentertoMousePointer.y, PudgeCentertoMousePointer.x));
		break;
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
