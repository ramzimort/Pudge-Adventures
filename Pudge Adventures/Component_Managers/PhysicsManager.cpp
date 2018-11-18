#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include "FrameRateController.h"
#include "..\Events\Collide.h"


extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;
extern FrameRateController* gpFRC;

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Init()
{
}

void PhysicsManager::Update(float FrameTime)
{
	// Integrate all body components
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
		if (pBody != nullptr)
			pBody->Integrate(-1000.f, FrameTime);
	}

	// Reset previous contacts
	gpCollisionManager->Reset();

	// Check for intersections
	auto pObj1 = gpGameObjectManager->mGameObjects.begin();
	auto pObjLast = gpGameObjectManager->mGameObjects.end();
	for (auto pObj1 = gpGameObjectManager->mGameObjects.begin(); pObj1 != pObjLast; ++pObj1)
	{
		Body* pBody1 = static_cast<Body*>((*pObj1)->GetComponent(BODY));
		if (pBody1 == nullptr)
			continue;
		if (pBody1->mType != INTERACTIVE)
			continue;
		for (auto pObj2 = gpGameObjectManager->mGameObjects.begin(); pObj2 != pObjLast; ++pObj2)
		{
			Body* pBody2 = static_cast<Body*>((*pObj2)->GetComponent(BODY));
			if (pBody2 == nullptr)
				continue;
			if (pBody2->mType != RIGID)
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
		if (mContact.first->mBodies[1]->mType == RIGID)		// All collisions with RIGID bodies
		{           
			Body* pInteractiveBody = mContact.first->mBodies[0];
			glm::vec2 offset = mContact.second;
			if (offset.y != 0.0f)							// Vertical Collision!
			{
				pInteractiveBody->mVel.y = 0.f;	// Set vertical speed to 0
				if (offset.y > 0)							// Apply Friction
					pInteractiveBody->mForce += -0.01*pInteractiveBody->mVel.x*pInteractiveBody->mMass/gpFRC->GetFrameTime();
			}
			if (offset.x != 0.0f)
				mContact.first->mBodies[0]->mVel.x = 0.f;
			
			mContact.first->mBodies[0]->mPos += offset;

		}
		//std::cout << "Collision!" << std::endl;
		//if(mContact->mBodies[0]->mpOwner->HasComponent(OBSTACLE) && mContact->mBodies[1]->mpOwner->HasComponent(INTERACTIVE))
		//CollideEvent ce;
		//mContact->mBodies[0]->mpOwner->HandleEvent(&ce);
		//mContact->mBodies[1]->mpOwner->HandleEvent(&ce);
	}
}
