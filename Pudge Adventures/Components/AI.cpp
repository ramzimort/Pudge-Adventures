#include "AI.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Component_Managers\EventManager.h"
#include "Transform.h"
#include "Body.h"
#include "GameObject.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\Event.h"
#include "..\Events\CameraMove.h"
#include <glm/vec2.hpp>

extern FrameRateController* gpFRC;
extern ObjectFactory* gpObjectFactory;
extern EventManager* gpEventManager;

botAI::botAI() :	
	Component(BOTAI),
	changeDirectionInterval(0.0f),
	currentTime(0.0f) { }

botAI::~botAI() 
{
	gpEventManager->Unsubscribe(CAMERA_MOVE, mpOwner);
}

void botAI::Init()
{
	currentTime = changeDirectionInterval;
	isAwake = false;
	gpEventManager->Subscribe(CAMERA_MOVE, mpOwner);

	ProjectileOffset *= static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mScale.x;
}

void botAI::Update()
{
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	if (isAwake)
	{
		if (pBody != nullptr)
			pBody->mVel.x = -1.f*speed;

		currentTime -= gpFRC->GetFrameTime();
		if (currentTime < 0)
		{
			speed *= -1.f;
			currentTime = changeDirectionInterval;
			mpOwner->HandleEvent(&Event(MIRROR_OBJECT));
			ShootProjectile();
		}
	}
	else
		pBody->mVel.x = 0.f;
}

void botAI::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["AI"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "MoveInterval")
			changeDirectionInterval = ComponentValues.value.GetFloat();
		else if (componentValueName == "Speed")
			speed = ComponentValues.value.GetFloat();
		else if (componentValueName == "Projectile")
			ProjectileName = ComponentValues.value.GetString();
		else if (componentValueName == "ProjectileSpeed")
			projectileSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "ProjectileOffset")
			ProjectileOffset = glm::vec2(ComponentValues.value.GetArray()[0].GetFloat(), ComponentValues.value.GetArray()[1].GetFloat());
	}
}

void botAI::HandleEvent(Event * pEvent)
{
	switch (pEvent->mType)
	{
	case CAMERA_MOVE:
		CheckCamera(pEvent);
		break;
	}

}

void botAI::ShootProjectile()
{
	GameObject* projectile = gpObjectFactory->LoadObject(ProjectileName);
	Transform* pTr = static_cast<Transform*>(projectile->GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(projectile->GetComponent(BODY));
	if (pTr != nullptr)
	{
		pTr->mPosition = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition + ProjectileOffset;
		projectile->Init();
		pBody->mVel.x = projectileSpeed;
		if (static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel.x < 0.f)
			pBody->mVel.x *= -1.f;
	}
}

void botAI::CheckCamera(Event* pEvent)
{
	CameraMoveEvent* CameraMove = static_cast<CameraMoveEvent*>(pEvent);
	
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));

	float
		L = CameraMove->currentPos.x - CameraMove->SCR_WIDTH / 2.f,
		R = CameraMove->currentPos.x + CameraMove->SCR_WIDTH / 2.f,
		U = CameraMove->currentPos.y + CameraMove->SCR_HEIGHT / 2.f,
		B = CameraMove->currentPos.y - CameraMove->SCR_HEIGHT / 2.f;


	if (pBody->mPos.x > L && pBody->mPos.x < R && pBody->mPos.y < U && pBody->mPos.y > B)
		isAwake = true;
	else
		isAwake = false;
}
