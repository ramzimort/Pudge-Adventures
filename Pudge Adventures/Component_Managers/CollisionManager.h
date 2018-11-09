#pragma once

#include <list>
#include <glm/glm.hpp>

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
		bool checkCollisionandGenerateContact(	Shape* pShape1,
												Shape* pShape2,
												std::list<Contact*> &Contacts);

	public:
		std::list<Contact*> mContacts;

		bool(*CollisionFunctions[2][2])(Shape* pShape1,
										Shape* pShape2,
										std::list<Contact*> &Contacts);
};