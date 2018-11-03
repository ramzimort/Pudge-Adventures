#include "Body.h"
#include "Transform.h"
#include "GameObject.h"
#include "..\Component_Managers\CollisionManager.h"
#include <string>

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
		inFile >> pAABB->mLeft;
		inFile >> pAABB->mTop;
		inFile >> pAABB->mRight;
		inFile >> pAABB->mBottom;
	}
}

void Body::Initialize()
{
	Transform* pTr = static_cast<Transform*> (mpOwner->GetComponent(TRANSFORM));
	if (pTr != nullptr)
	{
		mPos.x = pTr->mPosition.x;
		mPos.y = pTr->mPosition.y;
		mPrevPos = mPos;
	}
}

void Body::Integrate(float Gravity, float dt)
{
	// Save current position
	mPrevPos = mPos;

	// Compute Acceleration
	mForce.y += Gravity;
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

	Transform* pTr = static_cast<Transform*> (mpOwner->GetComponent(TRANSFORM));
	pTr->mPosition.x = mPos.x;
	pTr->mPosition.y = mPos.y;
}
