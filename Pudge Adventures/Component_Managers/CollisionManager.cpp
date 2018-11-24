#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "..\Components\Transform.h"
#include <glm/gtx/norm.hpp>
#include <algorithm>
#include <iostream>	




Contact::Contact()
{
	mBodies[0] = nullptr;
	mBodies[1] = nullptr;
}

Contact::~Contact()
{
}

bool CheckCollisionCircleCircle(Shape* pShape1, Shape* pShape2, std::list<std::pair<Contact*, glm::vec2>> &Contacts);
bool CheckCollisionCircleAABB(Shape* pShape1, Shape* pShape2, std::list<std::pair<Contact*, glm::vec2>> &Contacts);
bool CheckCollisionAABBCircle(Shape* pShape1, Shape* pShape2, std::list<std::pair<Contact*, glm::vec2>> &Contacts);
bool CheckCollisionAABBAABB(Shape* pShape1, Shape* pShape2, std::list<std::pair<Contact*, glm::vec2>> &Contacts);

CollisionManager::CollisionManager()
{
	CollisionFunctions[CIRCLE][CIRCLE] = CheckCollisionCircleCircle;
	CollisionFunctions[CIRCLE][AABB] = CheckCollisionCircleAABB;
	CollisionFunctions[AABB][CIRCLE] = CheckCollisionAABBCircle;
	CollisionFunctions[AABB][AABB] = CheckCollisionAABBAABB;
}

CollisionManager::~CollisionManager()
{
	for (auto c : mContacts)
		delete c.first;
}

void CollisionManager::Reset()
{
	for (auto c : mContacts)
		delete c.first;
	mContacts.clear();
}

bool CollisionManager::checkCollisionandGenerateContact(Shape * pShape1, Shape * pShape2, std::list<std::pair<Contact*, glm::vec2>>& Contacts)
{
	return CollisionFunctions[pShape1->mType][pShape2->mType](pShape1, pShape2, mContacts);
}


bool CheckCollisionCircleCircle(
	Shape* pShape1,		
	Shape* pShape2,
	std::list<std::pair<Contact*, glm::vec2>> &Contacts)
{
	ShapeCircle* C1 = static_cast<ShapeCircle*>(pShape1);
	ShapeCircle* C2 = static_cast<ShapeCircle*>(pShape2);

	glm::vec2
		Center1 = C1->mpOwnerBody->mColliderCenter,
		Center2 = C2->mpOwnerBody->mColliderCenter;
	//Intersection!
	if ((C1->mRadius + C2->mRadius)*(C1->mRadius + C2->mRadius) >= glm::distance2(Center1, Center2)) 
	{
		glm::vec2 deltaPos(0.f);
		//Create a new contact and add it
		Contact* pNewContact = new Contact();
		pNewContact->mBodies[0] = pShape1->mpOwnerBody;
		pNewContact->mBodies[1] = pShape2->mpOwnerBody;
		Contacts.push_back(std::pair<Contact*,glm::vec2>(pNewContact, deltaPos));
		return true;
	}
	return false;
}

bool CheckCollisionCircleAABB(	Shape* pShape1,
								Shape* pShape2,
	std::list<std::pair<Contact*, glm::vec2>> &Contacts)
{
	ShapeCircle* C1 = static_cast<ShapeCircle*>(pShape1);
	ShapeAABB* S2 = static_cast<ShapeAABB*>(pShape2);
	
	glm::vec2 
		Center1 = C1->mpOwnerBody->mColliderCenter,
		Center2 = S2->mpOwnerBody->mColliderCenter;
	float
		L1 = Center1.x - C1->mRadius,
		R1 = Center1.x + C1->mRadius,
		U1 = Center1.y + C1->mRadius,
		B1 = Center1.y - C1->mRadius,
		L2 = Center2.x - S2->mWidth  / 2.f,
		R2 = Center2.x + S2->mWidth  / 2.f,
		U2 = Center2.y + S2->mHeight / 2.f,
		B2 = Center2.y - S2->mHeight / 2.f;

	//std::cout << L1 << " " << R1 << " " << U1 << " " << B1 << std::endl;
	//std::cout << L2 << " " << R2 << " " << U2 << " " << B2 << std::endl << std::endl;

	// 8 different cases for CIRCLE location wrt AABB
	// West 
	if (L1 > R2)
		return false;
	if (L2 > R1)
		return false;
	if (B1 > U2)
		return false;
	if (B2 > U1)
		return false;
	//// NorthWest
	//if (Center1.x < L2 && Center1.y > U2)
	//	if (glm::length2(Center1 - glm::vec2(L2, U2)) > C1->mRadius*C1->mRadius)
	//		return false;
	//// Northeast
	//if (Center1.x > R2 && Center1.y > U2)
	//	if (glm::length2(Center1 - glm::vec2(R2, U2)) > C1->mRadius*C1->mRadius)
	//		return false;
	//// Southwest
	//if (Center1.x < L2 && Center1.y < B2)
	//	if (glm::length2(Center1 - glm::vec2(L2, B2)) > C1->mRadius*C1->mRadius)
	//		return false;
	//// Southeast
	//if (Center1.x > R2 && Center1.y < B2)
	//	if (glm::length2(Center1 - glm::vec2(R2, B2)) > C1->mRadius*C1->mRadius)
	//		return false;


	glm::vec2 C2C1 = C1->mpOwnerBody->mPos - S2->mpOwnerBody->mPos;
	float centerDistance = glm::length(C2C1);

	glm::vec2 deltaPos = C2C1 / centerDistance;
	deltaPos *= C1->mRadius + std::min(S2->mWidth, S2->mHeight) - centerDistance;
	//Create a new contact and add itd
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pShape2->mpOwnerBody;
	Contacts.push_back(std::pair<Contact*, glm::vec2>(pNewContact, deltaPos));
	return true;
}

bool CheckCollisionAABBCircle(	
	Shape* pShape1,					
	Shape* pShape2,
	std::list<std::pair<Contact*, glm::vec2>> &Contacts)
{
	//Add code to invert last inserted deltaPos
	return CheckCollisionCircleAABB(pShape2, pShape1, Contacts);
}

bool CheckCollisionAABBAABB(
	Shape* pShape1,
	Shape* pShape2,
	std::list<std::pair<Contact*, glm::vec2>> &Contacts)
{
	ShapeAABB* S1 = static_cast<ShapeAABB*>(pShape1);
	ShapeAABB* S2 = static_cast<ShapeAABB*>(pShape2);

	float	L1 = S1->mpOwnerBody->mColliderCenter.x - S1->mWidth / 2.f,
			R1 = S1->mpOwnerBody->mColliderCenter.x + S1->mWidth / 2.f,
			U1 = S1->mpOwnerBody->mColliderCenter.y + S1->mHeight / 2.f,
			B1 = S1->mpOwnerBody->mColliderCenter.y - S1->mHeight / 2.f,
			L2 = S2->mpOwnerBody->mColliderCenter.x - S2->mWidth / 2.f,
			R2 = S2->mpOwnerBody->mColliderCenter.x + S2->mWidth / 2.f,
			U2 = S2->mpOwnerBody->mColliderCenter.y + S2->mHeight / 2.f,
			B2 = S2->mpOwnerBody->mColliderCenter.y - S2->mHeight / 2.f;

	if (L1 > R2)
		return false;
	if (L2 > R1)
		return false;
	if (B1 > U2)
		return false;
	if (B2 > U1)
		return false;

	glm::vec2 deltaPos(0.0f);
	bool	North	= false, 
			East	= false,
			West	= false,
			South	= false;
	//Check Collision Directions:
	if (B1 <= U2 && B2 <= U1 && B1 >= B2 && U1 >= U2)
 		North = true;
	else if (B2 <= U1 && B1 <= U2 && B2 >= B1 && U2 >= U1)
		South = true;
	if (R1 >= L2 && R1 <= R2 && L1 <= L2 && L1 <= R2)
		West = true;
	else if (R2 >= L1 && R2 <= R1 && L2 <= L1 && L2 <= R1)
		East = true;

	// Modify offsets
	if (North)
		deltaPos.y += U2 - B1;
	else if (South)
		deltaPos.y -= U1 - B2;
	if (West)
		deltaPos.x -= R1 - L2;
	else if (East)
		deltaPos.x += R2 - L1;

	if (North && West || North && East || South && West || South && East)
	{
		if (glm::abs(deltaPos.x) > glm::abs(deltaPos.y))
			deltaPos.x = 0.f;
		else
			deltaPos.y = 0.f;
	}

	//std::cout << deltaPos.x << " " << deltaPos.y << std::endl;



	//Check y collision?
	//Create a new contact and add itd
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pShape2->mpOwnerBody;

	Contacts.push_back(std::pair<Contact*, glm::vec2>(pNewContact, deltaPos));
	return true;
}