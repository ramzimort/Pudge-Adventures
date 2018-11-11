#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "..\Components\Transform.h"
#include <glm/gtx/norm.hpp>
#include <iostream>





Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;
}

Contact::~Contact()
{
}

bool CheckCollisionCircleCircle(Shape* pShape1, Shape* pShape2, std::list<Contact*> &Contacts);
bool CheckCollisionCircleAABB(Shape* pShape1, Shape* pShape2, std::list<Contact*> &Contacts);
bool CheckCollisionAABBCircle(Shape* pShape1, Shape* pShape2, std::list<Contact*> &Contacts);
bool CheckCollisionAABBAABB(Shape* pShape1, Shape* pShape2, std::list<Contact*> &Contacts);

CollisionManager::CollisionManager()
{
	CollisionFunctions[CIRCLE][CIRCLE] = CheckCollisionCircleCircle;

	// Do the same for aabb circle, circle aabb, and aabb aabb
	CollisionFunctions[CIRCLE][AABB] = CheckCollisionCircleAABB;
	CollisionFunctions[AABB][CIRCLE] = CheckCollisionAABBCircle;
	CollisionFunctions[AABB][AABB] = CheckCollisionAABBAABB;
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

bool CheckCollisionCircleAABB(	Shape* pShape1,
								Shape* pShape2,
								std::list<Contact*> &Contacts)
{
	return false;
}

bool CheckCollisionAABBCircle(Shape* pShape1,
	Shape* pShape2,
	std::list<Contact*> &Contacts)
{
	return false;
}

bool CheckCollisionAABBAABB(Shape* pShape1,
	Shape* pShape2,
	std::list<Contact*> &Contacts)
{
	return false;
}