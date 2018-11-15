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
	INTERACTIVE,
	HOOK
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
	void Serialize(std::ifstream& inFile);
	void Serialize(rapidjson::Document& objectFile);
	void Integrate(float Gravity, float dt);
	void HandleEvent(Event* pEvent);

public:
	glm::vec2 mPos;
	glm::vec2 mPrevPos;
	glm::vec2 mVel;
	glm::vec2 mPrevVel;
	glm::vec2 mAcc;
	glm::vec2 mForce;
	float mMass, mInvMass;

	Shape* mpShape;
	BodyType mType;
};