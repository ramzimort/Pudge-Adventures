#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "..\Component_Managers\CollisionManager.h"
#include <string>
#include "..\Events\PlayerMove.h"

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
{
}

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
	mAcc(0.0f),
	mForce(0.0f),
	mMass(0.0f), mInvMass(0.0f),
	mpShape(nullptr)
{ }

Body::~Body()
{
}

void Body::Init()
{

}

void Body::Update()
{
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
	}
}

void Body::Integrate(float Gravity, float dt)
{
	if (mMass != 0.0f)
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

		// Zero all applied forces
		mForce = { 0.0f,0.0f };
	}

	Transform* pTr = static_cast<Transform*> (mpOwner->GetComponent(TRANSFORM));
	pTr->mPosition = mPos;
}

void Body::HandleEvent(Event * pEvent)
{
	if (pEvent->mType == PLAYER_MOVE)
	{
		PlayerMoveEvent* PME = static_cast<PlayerMoveEvent*>(pEvent);
		switch (PME->aType)
		{
		case MOVE_LEFT:
			mForce.x -= 1000.f;
			break;
		case MOVE_RIGHT:
			mForce.x += 1000.0f;
			break;
		case JUMP:
			mForce.y += 10000.0f;
			break;
		}
	}
}
