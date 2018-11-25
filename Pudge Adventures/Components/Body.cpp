#include "Body.h"
#include "GameObject.h"
#include "Transform.h"
#include "..\Component_Managers\CollisionManager.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\UpdateBody.h"
#include "..\Events\RotateBody.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>

Shape::Shape(ShapeType Type) : 
	mType(Type),
	mpOwnerBody(nullptr)
{ }
ShapeCircle::ShapeCircle() : 
	Shape(CIRCLE), 
	mRadius(0.f)
{ }
ShapeCircle::~ShapeCircle()
{ }
bool ShapeCircle::testPoint(glm::vec2& Point)
{
	return ((mpOwnerBody->mPos.x - Point.x)*(mpOwnerBody->mPos.x - Point.x) +
		(mpOwnerBody->mPos.y - Point.y)*(mpOwnerBody->mPos.y - Point.y)
		< mRadius*mRadius);
}
ShapeAABB::ShapeAABB() : 
	Shape(AABB),
	mWidth(0.f),
	mHeight(0.f)
{ }
ShapeAABB::~ShapeAABB()
{ }
bool ShapeAABB::testPoint(glm::vec2& Point)
{
	if (Point.x < (mpOwnerBody->mPos.x - mWidth / 2))
		return false;
	if (Point.x > (mpOwnerBody->mPos.x + mWidth / 2))
		return false;
	if (Point.y < (mpOwnerBody->mPos.y - mHeight / 2))
		return false;
	if (Point.y > (mpOwnerBody->mPos.y + mHeight / 2))
		return false;
	return true;
}


Body::Body() : Component(BODY),
	mPos(0.0f), 
	mPrevPos(0.0f),
	mVel(0.0f),
	mAcc(0.0f),
	mForce(0.0f),
	mMass(0.0f), mInvMass(0.0f),
	mColliderCenter(0.f),
	mPos_mPivot(0.f),
	mPivot_mColliderCenter(0.f),
	mpShape(nullptr),
	mType(NONE)
{ }
Body::~Body()
{
	if (mpShape != nullptr)
		delete mpShape;
}
void Body::Init()
{ 
	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	if (pTr != nullptr)
	{
		mPos = pTr->mPosition;
		mPos_mPivot = pTr->mRotationCenter * pTr->mScale;
		mColliderCenter = mColliderCenter * pTr->mScale;
		mColliderCenter += mPos;
		mPivot_mColliderCenter = mColliderCenter - (mPos + mPos_mPivot);
	}
}
void Body::Update()
{
	UpdatePositionEvent UpdatePosition;
	UpdatePosition.newPosition = mPos;
	mpOwner->HandleEvent(&UpdatePosition);
	
}
void Body::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["Body"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "Mass") {
			mMass = ComponentValues.value.GetFloat();
			if (mMass != 0.0f)
				mInvMass = 1.0f / mMass;
			else
				mInvMass = 0.0f;
		}
		else if (componentValueName == "Shape")
		{
			std::string shapeType = ComponentValues.value.GetString();
			if (shapeType == "Circle")
			{
				mpShape = new ShapeCircle();
				mpShape->mpOwnerBody = this;
			}
			else if (shapeType == "AABB")
			{
				mpShape = new ShapeAABB();
				mpShape->mpOwnerBody = this;
			}
		}
		else if (componentValueName == "Radius")
		{
			ShapeCircle* pCircle = static_cast<ShapeCircle*>(mpShape);
			if (pCircle != nullptr)
				pCircle->mRadius = ComponentValues.value.GetFloat();
		}
		else if (componentValueName == "Width")
		{
			ShapeAABB* pAABB = static_cast<ShapeAABB*>(mpShape);
			if (pAABB != nullptr)
				pAABB->mWidth = ComponentValues.value.GetFloat();
		}
		else if (componentValueName == "Height")
		{
			ShapeAABB* pAABB = static_cast<ShapeAABB*>(mpShape);
			if (pAABB != nullptr)
				pAABB->mHeight = ComponentValues.value.GetFloat();
		}
		else if (componentValueName == "Type")
		{
			std::string objectType = ComponentValues.value.GetString();
			if (objectType == "Rigid")
				mType = RIGID;
			else if (objectType == "Pudge")
				mType = PUDGE;
			else if (objectType == "Enemy")
				mType = ENEMY;
			else if (objectFile == "Cleaver")
				mType = CLEAVER;
			else if (objectType == "Hook")
				mType = HOOK;
			else if (objectType == "Rune")
				mType = RUNE;
			else
				mType = NONE;
		}
		else if (componentValueName == "xColliderCenter")
			mColliderCenter.x = ComponentValues.value.GetFloat();
		else if (componentValueName == "yColliderCenter")
			mColliderCenter.y = ComponentValues.value.GetFloat();
	}
}
void Body::Integrate(float Gravity, float dt)
{
	// Save current position
	mPrevPos = mPos; 
	// Compute Acceleration
	mForce.y += mMass * Gravity;
	mAcc.x = mForce.x * mInvMass;
	mAcc.y = mForce.y * mInvMass;
	// Intergrate the velocity
	mVel.x += mAcc.x * dt;
	mVel.y += mAcc.y * dt;

	// Integrate the position
	mPos.x += mVel.x * dt;
	mPos.y += mVel.y * dt;

	if (isHaste)
		mPos += mVel * dt;

	// Zero all applied forces
	mForce = { 0.0f,0.0f };
	UpdateBodyEvent UpdateBodyPosition;
	UpdateBodyPosition.newPosition = mPos;
	mpOwner->HandleEvent(&UpdateBodyPosition);
}

void Body::HandleEvent(Event * pEvent)
{
	switch (pEvent->mType)
	{
	case MOVE_LEFT:
		mForce.x -= 5000.f;
		break;
	case MOVE_RIGHT:
		mForce.x += 5000.0f;
		break;
	case JUMP:
		mForce.y += 400000.0f;
		break;
	case UPDATE_BODY:
	{
		mPos = static_cast<UpdateBodyEvent*>(pEvent)->newPosition;
		mColliderCenter = mPos + mPos_mPivot + mPivot_mColliderCenter;
		UpdatePositionEvent UpdatePosition;
		UpdatePosition.newPosition = mPos;
		mpOwner->HandleEvent(&UpdatePosition);
		break;

	}
	case ROTATE_BODY:
		mPivot_mColliderCenter =
			static_cast<glm::vec2>(glm::rotate(glm::mat4(), static_cast<RotateBodyEvent*>(pEvent)->deltaAngle, glm::vec3(0, 0, 1))*
				glm::vec4(mPivot_mColliderCenter, 0.f, 0.f));
		break;
	case MIRROR_OBJECT:
		mPos_mPivot.x = -mPos_mPivot.x;
		mPivot_mColliderCenter.x = -mPivot_mColliderCenter.x;
		mColliderCenter = mPos + mPos_mPivot + mPivot_mColliderCenter;
		break;
	case ENABLE_HASTE:
		isHaste = true;
		break;
	case DISABLE_HASTE:
		isHaste = false;
		break;
	}

}
