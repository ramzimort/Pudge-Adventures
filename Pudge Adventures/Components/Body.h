
/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Body.h
Purpose: Component that handles physics attributes of object
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/


#pragma once

#include "Component.h"
#include <glm/glm.hpp>


class Body;
enum ShapeType
{
	CIRCLE,
	AABB,
};
enum BodyType {
	NONE,
	RIGID,
	PUDGE,
	ENEMY,
	HOOK,
	CLEAVER,
	PROJECTILE,
	RUNE,
	BODYNUM
};

class Shape
{
public:
	Shape(ShapeType Type);
	virtual ~Shape() {};
	virtual bool testPoint(glm::vec2& Point) = 0;

public:
	Body* mpOwnerBody;
	ShapeType mType;
};

class ShapeCircle : public Shape
{
public:
	ShapeCircle();
	~ShapeCircle();

	bool testPoint(glm::vec2& Point);

public:
	float mRadius;
};
class ShapeAABB : public Shape
{
public:
	ShapeAABB();
	~ShapeAABB();

	bool testPoint(glm::vec2& Point);

public:
	float mWidth, mHeight;
};

class Body : public Component
{
public:
	Body();
	~Body();

	void Init();
	void Update();
	void Serialize(rapidjson::Document& objectFile);
	void Integrate(float Gravity, float dt);
	void HandleEvent(Event* pEvent);

public:
	glm::vec2 mPos;
	glm::vec2 mPrevPos;
	glm::vec2 mVel;
	glm::vec2 mAcc;
	float mMass, mInvMass;
	float moveSpeed;
	float jumpPulse;

	Shape* mpShape;
	BodyType mType;
	glm::vec2				mColliderCenter;	// Center of Collider

public:
	glm::vec2				mPos_mPivot;
	glm::vec2				mPivot_mColliderCenter;
	float					isMirrored;

private:
	bool isHaste = false;
};