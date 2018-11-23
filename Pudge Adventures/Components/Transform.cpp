
#include "Transform.h"
#include "GameObject.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\RotateTowardPointer.h"
#include "..\Events\SetAngle.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\RotateBody.h"
#include "..\Events\MirrorObject.h"
#include "..\Events\MIrrorArms.h"
#include "..\Events\PlayerMove.h"
#include <iostream>

constexpr auto PI = 3.14159265358979323846f;

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
	//InitializeBodyEvent InitializeBody;
	//InitializeBody.InitialPosition = mPosition;
	//InitializeBody.mScale = mScale;
	//InitializeBody.InitialAngle = mAngle;
	//InitializeBody.mPivot = mRotationCenter * mScale;
	//mpOwner->HandleEvent(&InitializeBody);
}

void Transform::Update() { }

void Transform::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case PLAYER_MOVE:
		if (static_cast<PlayerMoveEvent*>(pEvent)->aType == MOVE_LEFT && mScale.x < 0.f ||
			static_cast<PlayerMoveEvent*>(pEvent)->aType == MOVE_RIGHT && mScale.x > 0.f)
		{
			MirrorObjectEvent MirrorObject;
			mpOwner->HandleEvent(&MirrorObject);
		}
		break;
	case UPDATE_POSITION:
		mPosition = static_cast<UpdatePositionEvent*>(pEvent)->newPosition;
		break;
	case MIRROR_OBJECT:
		mScale.x *= -1.f;
		break;
	case SET_ANGLE:
		RotateBody(mAngle - static_cast<SetAngleEvent*>(pEvent)->mAngle);
		mAngle = static_cast<SetAngleEvent*>(pEvent)->mAngle;
		break;
	}
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

void Transform::RotateBody(float deltaAngle)
{
	if (mScale.x > 0.f)
		deltaAngle *= -1.f;
	RotateBodyEvent RotateBody;
	RotateBody.deltaAngle = deltaAngle;
	RotateBody.mPivot = glm::vec2(mRotationCenter.x*mScale.x, mRotationCenter.y*mScale.y);
	mpOwner->HandleEvent(&RotateBody);
}