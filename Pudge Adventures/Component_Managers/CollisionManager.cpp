#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "..\Components\Transform.h"
#include <glm/gtx/norm.hpp>
#include <algorithm>





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
	//Intersection!

	

	if ((C1->mRadius + C2->mRadius)*(C1->mRadius + C2->mRadius) >= glm::distance2(C1->mpOwnerBody->mPos, C2->mpOwnerBody->mPos)) {
		glm::vec2 C2C1 = C1->mpOwnerBody->mPos - C2->mpOwnerBody->mPos;
		float centerDistance = glm::length(C2C1);

		glm::vec2 deltaPos = C2C1 / centerDistance;
		deltaPos *= C1->mRadius + C2->mRadius - centerDistance;
		//Create a new contact and add itd
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

	float 
		C1_L = C1->mpOwnerBody->mPos.x - C1->mRadius,
		C1_R = C1->mpOwnerBody->mPos.x + C1->mRadius,
		C1_U = C1->mpOwnerBody->mPos.y + C1->mRadius,
		C1_B = C1->mpOwnerBody->mPos.y - C1->mRadius,
		S2_L = S2->mpOwnerBody->mPos.x - S2->mWidth / 2.f,
		S2_R = S2->mpOwnerBody->mPos.x + S2->mWidth / 2.f,
		S2_U = S2->mpOwnerBody->mPos.y + S2->mHeight / 2.f,
		S2_B = S2->mpOwnerBody->mPos.y - S2->mHeight / 2.f;
	if (S2_L > C1_R)
		return false;
	if (C1_L > S2_R)
		return false;
	if (C1_B > S2_U)
		return false;
	if (S2_B > C1_U)
		return false;

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

	float	S1_L = S1->mpOwnerBody->mPos.x - S1->mWidth / 2.f,
			S1_R = S1->mpOwnerBody->mPos.x + S1->mWidth / 2.f,
			S1_U = S1->mpOwnerBody->mPos.y + S1->mHeight / 2.f,
			S1_B = S1->mpOwnerBody->mPos.y - S1->mHeight / 2.f,
			S2_L = S2->mpOwnerBody->mPos.x - S2->mWidth / 2.f,
			S2_R = S2->mpOwnerBody->mPos.x + S2->mWidth / 2.f,
			S2_U = S2->mpOwnerBody->mPos.y + S2->mHeight / 2.f,
			S2_B = S2->mpOwnerBody->mPos.y - S2->mHeight / 2.f;

	if (S1_L > S2_R)
		return false;
	if (S2_L > S1_R)
		return false;
	if (S1_B > S2_U)
		return false;
	if (S2_B > S1_U)
		return false;

	glm::vec2 deltaPos(0.0f);
	//Check which collision
	if (S1_L < S2_R)
		deltaPos.x = S2_R - S1_L;
	if (S2_L < S1_R)
		deltaPos.x = S2_L - S1_R;
	if (S1_B < S2_U)
		deltaPos.x = S2_U - S1_B;
	if (S2_B < S1_U)
		deltaPos.x = S2_B - S1_U;

	//Check y collision?
	//Create a new contact and add itd
	Contact* pNewContact = new Contact();
	pNewContact->mBodies[0] = pShape1->mpOwnerBody;
	pNewContact->mBodies[1] = pShape2->mpOwnerBody;

	Contacts.push_back(std::pair<Contact*, glm::vec2>(pNewContact, deltaPos));
	return true;
}