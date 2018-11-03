#pragma once

#include <list>

class Body;

class Shape
{
public:
	enum ShapeType
	{
		CIRCLE,
		AABB,
	};

	Shape(ShapeType Type);
	virtual ~Shape() {};
	virtual bool testPoint(float Pointx, float PointY) = 0;

public:
	Body* mpOwnerBody;
	ShapeType mType;
};

class ShapeCircle : public Shape
{
public:
	ShapeCircle();
	~ShapeCircle();

	bool testPoint(float PointX, float PointY);

public:
	float mRadius;
};

class ShapeAABB : public Shape
{
public:
	ShapeAABB();
	~ShapeAABB();

	bool testPoint(float PointX, float PointY);

public:
	float mTop, mBottom, mRight, mLeft;
};


class Contact
{	
	public:
		Body* mBodies[2];

	public:
		Contact();
		~Contact();
};

class CollisionManager
{
	public:
		CollisionManager();
		~CollisionManager();

		void Reset();
		bool checkCollisionandGenerateContact(	Shape* pShape1, float pos1X, float pos1Y,
												Shape* pShape2, float pos2X, float pos2Y,
												std::list<Contact*> &Contacts);

	public:
		std::list<Contact*> mContacts;
		bool(*CollisionFunctions[2][2])(Shape* pShape1, float pos1X, float pos1Y,
										Shape* pShape2, float pos2X, float pos2Y,
										std::list<Contact*> &Contacts);
};