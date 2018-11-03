#include "CollisionManager.h"


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

bool ShapeCircle::testPoint(float PointX, float PointY)
{
	return false;
}

ShapeAABB::ShapeAABB() : Shape(AABB)
{
	mTop = mBottom = mRight = mLeft = 0.0f;
}

ShapeAABB::~ShapeAABB()
{
}

bool ShapeAABB::testPoint(float PointX, float PointY)
{
	return false;
}

Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;
}

Contact::~Contact()
{
}

CollisionManager::CollisionManager()
{
	//CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;
	// Do the same for aabb circle, circle aabb, and aabb aabb
	//CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;
	//CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;
	//CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;
}

CollisionManager::~CollisionManager()
{
	for (auto c : mContacts)
		delete c;
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c;
	mContacts.clear();
}

/*bool CollisionManager::checkCollisionandGenerateContact(Shape * pShape1, float pos1X, float pos1Y, Shape * pShape2, float pos2X, float pos2Y, std::list<Contact*>& Contacts)
{
	CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, pos1X, pos1Y, pShape2, pos2X, pos2Y, mContacts);
}


bool CheckCollisionCircleCircle(Shape* pShape1, float pos1X, float pos1Y,
								Shape* pShape2, float pos2X, float pos2Y,
					*/			std::list<Contact*> &Contacts)
{
	//Intersection!

	//Create a new contact and add it
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pShape2->mpOwnerBody;

	Contacts.push_back(pNewContact);

	return true;
}