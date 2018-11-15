#include "Body.h"
#include "GameObject.h"
#include "..\Component_Managers\CollisionManager.h"
#include "..\Events\PlayerMove.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\UpdateBody.h"
#include "..\Events\ScaleBody.h"
#include "..\Events\MirrorObject.h"
#include <string>
#include <iostream>

Shape::Shape(ShapeType Type)
{
	mType = Type;
	mpOwnerBody = nullptr;
}
ShapeCircle::ShapeCircle() : Shape(CIRCLE)
{
	mRadius = 0.0f;
}
ShapeCircle::~ShapeCircle()
{ }
bool ShapeCircle::testPoint(glm::vec2& Point)
{
	return ((mpOwnerBody->mPos.x - Point.x)*(mpOwnerBody->mPos.x - Point.x) +
		(mpOwnerBody->mPos.y - Point.y)*(mpOwnerBody->mPos.y - Point.y)
		< mRadius*mRadius);
}
ShapeAABB::ShapeAABB() : Shape(AABB)
{
	mWidth = mHeight = 0.0f;
}
ShapeAABB::~ShapeAABB()
{
}
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
	mPrevVel(0.0f),
	mAcc(0.0f),
	mForce(0.0f),
	mMass(0.0f), mInvMass(0.0f),
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

}

void Body::Update()
{
	UpdatePositionEvent UpdatePosition;
	UpdatePosition.newPosition = mPos;
	mpOwner->HandleEvent(&UpdatePosition);
	if(mpOwner->HasComponent(CONTROLLER))
	std::cout << "Prev: " << (float)mPrevVel.x << ", Current: " << (float)mVel.x << std::endl;
	if (mPrevVel.x > 0.f && mVel.x <= 0.f || mPrevVel.x < 0.f && mVel.x >= 0.f)
	{
		MirrorObjectEvent MirrorObject;
		mpOwner->HandleEvent(&MirrorObject);
	}

}

void Body::Serialize(std::ifstream & inFile)
{
	inFile >> mMass;
	if (mMass != 0.0f)
		mInvMass = 1.0f / mMass;
	else
		mInvMass = 0.0f;

	std::string shapeStype;
	inFile >> shapeStype;
	if (shapeStype == "Circle")
	{
		mpShape = new ShapeCircle();
		mpShape->mpOwnerBody = this;
		ShapeCircle* pCircle = static_cast<ShapeCircle*>(mpShape);
		inFile >> pCircle->mRadius;
	}
	else if (shapeStype == "AABB")
	{
		mpShape = new ShapeAABB();
		mpShape->mpOwnerBody = this;
		ShapeAABB* pAABB = static_cast<ShapeAABB*>(mpShape);
		inFile >> pAABB->mWidth;
		inFile >> pAABB->mHeight;
	}
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
			else if (objectType == "Interactive")
				mType = INTERACTIVE;
			else if (objectType == "Hook")
				mType = HOOK;
			else
				mType = NONE;
		}
	}
}

void Body::Integrate(float Gravity, float dt)
{
	if (mMass != 0.0f)
	{
		// Save current position
		mPrevPos = mPos;
		mPrevVel = mVel;
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

		// Zero all applied forces
		mForce = { 0.0f,0.0f };
	}
	UpdateBodyEvent UpdateBodyPosition;
	UpdateBodyPosition.newPosition = mPos;
	mpOwner->HandleEvent(&UpdateBodyPosition);

}

void Body::HandleEvent(Event * pEvent)
{
	switch (pEvent->mType)
	{
		case PLAYER_MOVE:
			switch (static_cast<PlayerMoveEvent*>(pEvent)->aType)
			{
			case MOVE_LEFT:
				mForce.x -= 5000.f;
				break;
			case MOVE_RIGHT:
				mForce.x += 5000.0f;
				break;
			case JUMP:
				mForce.y += 100000.0f;
				break;
			}
			break;
		case INITIALIZE_BODY:
			mPos = static_cast<InitializeBodyEvent*>(pEvent)->InitialPosition;
			break;
		case UPDATE_BODY:
			mPos = static_cast<UpdateBodyEvent*>(pEvent)->newPosition;
			break;
		case SCALE_BODY:
			switch (mpShape->mType)
			{
			case CIRCLE:
				static_cast<ShapeCircle*>(mpShape)->mRadius *= static_cast<ScaleBodyEvent*>(pEvent)->mScale.x;
				break;
			case AABB:
				static_cast<ShapeAABB*>(mpShape)->mWidth *= static_cast<ScaleBodyEvent*>(pEvent)->mScale.x;
				static_cast<ShapeAABB*>(mpShape)->mHeight *= static_cast<ScaleBodyEvent*>(pEvent)->mScale.y;
				break;
			}
			break;
	}

}
