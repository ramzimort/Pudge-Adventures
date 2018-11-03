#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"

extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Update(float FrameTime) {}
//{
//	// Integrate all body components
//	for (auto go : gpGameObjectManager->mGameObjects)
//	{
//		Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
//		if (pBody != nullptr)
//			pBody->Integrate(-100.f, FrameTime);
//	}
//
//	// Reset previous contacts
//	gpCollisionManager->Reset();
//
//	// Check for intersections
//	auto pObj1 = gpGameObjectManager->mGameObjects.begin();
//	auto pObjLast = gpGameObjectManager->mGameObjects.end();
//	while (pObj1 != pObjLast)
//	//{
//	//	Body* pBody = static_cast<Body*>(pObj1->GetComponent(BODY));
//	//	if (pBody != nullptr)
//	//		continue;
//	//	for (auto pObj2 = pObj1 + 1; pObj2 != pObjLast; ++pObj2)
//	//	{
//	//		Body* pBody = static_cast<Body*>(pObj2->GetComponent(BODY));
//	//		if (pBody != nullptr)
//	//			continue;
//	//		gpCollisionManager->checkCollisionandGenerateContact(
//	//			pBody1->
//	//		)
//	//	}
//	//	++pObj1;
//	
//
//	// Add own physics functions here
