#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include "..\Events\Collide.h"


extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Init()
{
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		Transform* pTr = static_cast<Transform*> (go->GetComponent(TRANSFORM));
		Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
		if (pBody != nullptr && pTr != nullptr)
			pBody->mPos.x = pTr->mPosition.x;
			pBody->mPos.y = pTr->mPosition.y;
			pBody->mPrevPos = pBody->mPos;
	}

}

void PhysicsManager::Update(float FrameTime)
{
	// Integrate all body components
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
		if (pBody != nullptr)
			pBody->Integrate(0.0f, FrameTime);
	}

	// Reset previous contacts
	gpCollisionManager->Reset();

	// Check for intersections
	auto pObj1 = gpGameObjectManager->mGameObjects.begin();
	auto pObj2 = gpGameObjectManager->mGameObjects.begin();
	auto pObjLast = gpGameObjectManager->mGameObjects.end();
	while (pObj1 != pObjLast)
	{
		Body* pBody1 = static_cast<Body*>((*pObj1)->GetComponent(BODY));
		++pObj1;
		if (pBody1 == nullptr)
			continue;
		for (pObj2 = pObj1; pObj2 != pObjLast; ++pObj2)
		{
			Body* pBody2 = static_cast<Body*>((*pObj2)->GetComponent(BODY));
			if (pBody2 == nullptr)
				continue;
			gpCollisionManager->checkCollisionandGenerateContact(
				pBody1->mpShape,
				pBody2->mpShape,
				gpCollisionManager->mContacts
			);
		}
	}
	// Add own physics functions here
	for (auto mContact : gpCollisionManager->mContacts)
	{
		CollideEvent ce;
		mContact->mBodies[0]->mpOwner->HandleEvent(&ce);
		mContact->mBodies[1]->mpOwner->HandleEvent(&ce);
	}
}
