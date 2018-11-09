#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "..\Components\Transform.h"
#include <glm/gtx/norm.hpp>
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
{
}

bool ShapeCircle::testPoint(glm::vec2& Point)
{
	return ((mpOwnerBody->mPos.x-Point.x)*(mpOwnerBody->mPos.x - Point.x) + 
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

Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;
}

Contact::~Contact()
{
}

bool CheckCollisionCircleCircle(Shape* pShape1, Shape* pShape2, std::list<Contact*> &Contacts);

CollisionManager::CollisionManager()
{
	CollisionFunctions[Shape::CIRCLE][Shape::CIRCLE] = CheckCollisionCircleCircle;

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

bool CollisionManager::checkCollisionandGenerateContact(Shape * pShape1, Shape * pShape2, std::list<Contact*>& Contacts)
{
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, pShape2, mContacts);
}


bool CheckCollisionCircleCircle(Shape* pShape1,
								Shape* pShape2,
								std::list<Contact*> &Contacts)
{
	ShapeCircle* C1 = static_cast<ShapeCircle*>(pShape1);
	ShapeCircle* C2 = static_cast<ShapeCircle*>(pShape2);
	//Intersection!

	if ((C1->mRadius + C2->mRadius)*(C1->mRadius + C2->mRadius) >= glm::distance2(C1->mpOwnerBody->mPos, C2->mpOwnerBody->mPos)) {

		std::cout << glm::distance2(C1->mpOwnerBody->mPos, C2->mpOwnerBody->mPos) << std::endl;
		//Create a new contact and add itd
		Contact* pNewContact = new Contact();
		pNewContact->mBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mBodies[1] = pShape2->mpOwnerBody;

		Contacts.push_back(pNewContact);

		return true;
	}
	return false;
}