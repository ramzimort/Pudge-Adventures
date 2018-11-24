#include "PhysicsManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "..\Components\GameObject.h"
#include "..\Components\Body.h"
#include "GameObjectManager.h"
#include "FrameRateController.h"
#include "..\Events\Collide.h"


extern GameObjectManager* gpGameObjectManager;
extern CollisionManager* gpCollisionManager;
extern EventManager* gpEventManager;
extern FrameRateController* gpFRC;

void noop(Body* pBody1, Body* pBody2, glm::vec2& offset);
void InteractiveRigid(Body* pBody1, Body* pBody2, glm::vec2& offset);
void HookRigid(Body* pBody1, Body* pBody2, glm::vec2& offset);
void HookPudge(Body* pBody1, Body* pBody2, glm::vec2& offset);
void HookInteractive(Body* pBody1, Body* pBody2, glm::vec2& offset);

PhysicsManager::PhysicsManager()
{
}

PhysicsManager::~PhysicsManager()
{
}

void PhysicsManager::Init()
{
	// Set all interaction types to no-op
	for (unsigned int i = 0; i < BODYNUM; ++i)
		for (unsigned int j = 0; j < BODYNUM; ++j)
			InteractionTypes[i][j] = noop;

	InteractionTypes[PUDGE][RIGID] = InteractiveRigid;
	InteractionTypes[ENEMY][RIGID] = InteractiveRigid;
	InteractionTypes[HOOK][RIGID] = HookRigid;
	InteractionTypes[HOOK][PUDGE] = HookPudge;
	InteractionTypes[HOOK][RUNE] = HookInteractive;

	// Reset contacts
	gpCollisionManager->Reset();
}

void PhysicsManager::Update(float FrameTime)
{
	/* ================================ Integrate Body Components S========================================== */
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		Body* pBody = static_cast<Body*>(go->GetComponent(BODY));
		if (pBody != nullptr)
			pBody->Integrate(-1000.f, FrameTime);
	}

	/* ================================ Reset Previous Collisions ========================================== */
	gpCollisionManager->Reset();

	/* ================================ Check for New Collisions ========================================== */
	auto pObj1 = gpGameObjectManager->mGameObjects.begin();
	auto pObjLast = gpGameObjectManager->mGameObjects.end();
	for (auto pObj1 = gpGameObjectManager->mGameObjects.begin(); pObj1 != pObjLast; ++pObj1)
	{
		Body* pBody1 = static_cast<Body*>((*pObj1)->GetComponent(BODY));
		if (pBody1 == nullptr)
			continue;
		for (auto pObj2 = gpGameObjectManager->mGameObjects.begin(); pObj2 != pObjLast; ++pObj2)
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
	/* ================================ Collision Interactions ========================================== */
	for (auto mContact : gpCollisionManager->mContacts)
	{
		Body* pBody1 = mContact.first->mBodies[0];
		Body* pBody2 = mContact.first->mBodies[1];
		glm::vec2 offset = mContact.second;
		InteractionTypes[pBody1->mType][pBody2->mType](pBody1, pBody2, offset);
	}
}

void noop(Body* pBody1, Body* pBody2, glm::vec2& a) { }
void InteractiveRigid(Body* pBody1, Body* pBody2, glm::vec2& offset)
{ 
	Body* pInteractiveBody = pBody1;
	Body* pRigidBody = pBody2;
	/* ================================ Vertical Collision ========================================== */
	if (offset.y != 0.0f) 						
	{
		pInteractiveBody->mVel.y = 0.f;										// Reset Vertical Velocity													
		if (offset.y > 0.f)
		{
			pInteractiveBody->mForce +=										// Apply Friction
				-0.01f*(pInteractiveBody->mVel.x)*(pInteractiveBody->mMass) 
				/ (gpFRC->GetFrameTime());									
			pInteractiveBody->mpOwner->HandleEvent(&Event(UNBLOCK_MOVE));	// Enable Movement													
		}
	}
	/* ================================ Horizontal Collision ========================================== */
	if (offset.x != 0.0f) // Horizontal Collision!
		pInteractiveBody->mVel.x = 0.f;										// Reset Vertical Velocity
	/* ================================ Object Separation ========================================== */
	pInteractiveBody->mPos += offset;
}
void HookRigid(Body* pBody1, Body* pBody2, glm::vec2& offset)
{
	/* ================================ Force Return Hook upon collision with rigid bodies ========================================== */
	gpEventManager->ForceTimedEvent(RETURN_HOOK);
}
void HookPudge(Body* pBody1, Body* pBody2, glm::vec2& offset)
{
	/* ================================ Grab hook once it collides with Pudge ========================================== */
	Event Grab_Hook(GRAB_HOOK);
	gpEventManager->BroadcaseEventToSubscribers(&Grab_Hook);
}
void HookInteractive(Body* pBody1, Body* pBody2, glm::vec2& offset)
{
	/* ================================ Attach Object Body to Hook Collider Center upon collision ========================================== */
	Body* hookBody = pBody1;
	Body* interactiveBody = pBody2;

	interactiveBody->mPos = hookBody->mPos + hookBody->mPos_mPivot + hookBody->mPivot_mColliderCenter;
}