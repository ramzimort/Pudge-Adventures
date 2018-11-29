
#include "botAI2.h"
#include "GameObject.h"
#include "Transform.h"
#include "Body.h"
#include "Sprite.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\CameraMove.h"
#include <iostream>

constexpr float PI = 3.14159265358979323846f;
float findAcuteAngle(glm::vec2 const& V1, glm::vec2 const& V2);

extern FrameRateController* gpFRC;
extern EventManager* gpEventManager;
extern ObjectFactory* gpObjectFactory;

botAI2::botAI2() :
	Component(BOTAI2),
	CurrentTime(0.f),
	AttackSpeed(0.f),
	ProjectileName(""),
	ProjectileSpeed(0.f),
	isAwake(false),
	Ballista_Pudge(0.f)
{ }

botAI2::~botAI2()
{ 

}

void botAI2::Init()
{ 
	isAwake = false;
	gpEventManager->Subscribe(UPDATE_POSITION, mpOwner);
	gpEventManager->Subscribe(CAMERA_MOVE, mpOwner);
	CurrentTime = AttackSpeed;
}

void botAI2::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["AI2"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "AttackSpeed")
			AttackSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "ProjectileSpeed")
			ProjectileSpeed = ComponentValues.value.GetFloat(); 
		else if (componentValueName == "Projectile")
			ProjectileName = ComponentValues.value.GetString();
	}
}

void botAI2::Update()
{
	glm::vec2 pos = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition;
	if (isAwake)
	{
		static_cast<Sprite*>(mpOwner->GetComponent(SPRITE))->enableAnimation = true;
		std::cout << "AttackTime: " << CurrentTime << std::endl;
		CurrentTime -= gpFRC->GetFrameTime();
		if (CurrentTime < 0.f)
		{
			CurrentTime = AttackSpeed;
			ShootProjectile();
		}
	}
	else
		static_cast<Sprite*>(mpOwner->GetComponent(SPRITE))->enableAnimation = false;
}

void botAI2::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case UPDATE_POSITION:
	{
		Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
		Ballista_Pudge = (static_cast<UpdatePositionEvent*>(pEvent)->newPosition - pTr->mPosition);
		float newAngle = findAcuteAngle(glm::vec2(0.f,1.f), Ballista_Pudge);
		pTr->mAngle = newAngle;
		break;
	}
	case CAMERA_MOVE:
		CheckCamera(pEvent);
		break;
	}
}


float findAcuteAngle(glm::vec2 const& V1, glm::vec2 const& V2)
{
	glm::vec2 v1 = glm::normalize(V1);
	glm::vec2 v2 = glm::normalize(V2);

	// Get proper angle
	float dotProduct = glm::dot(v1, v2);
	float newAngle;
	if (dotProduct > 1.f)
		newAngle = 0.f;
	else if (dotProduct < -1.f)
		newAngle = PI;
	else
		newAngle = acosf(dotProduct);

	glm::vec2 n1;
	n1.x = -1.f * v1.y;
	n1.y = v1.x;

	if (glm::dot(n1, v2) < 0)
		newAngle *= -1.f;

	return newAngle;
}

void botAI2::ShootProjectile()
{
	GameObject* projectile = gpObjectFactory->LoadObject(ProjectileName);
	Transform* pTr = static_cast<Transform*>(projectile->GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(projectile->GetComponent(BODY));
	if (pTr != nullptr)
	{
		pTr->mPosition = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition;
		pTr->mAngle = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mAngle;
		projectile->Init();
		pBody->mVel = glm::normalize(Ballista_Pudge)*ProjectileSpeed;
	}
}

void botAI2::CheckCamera(Event* pEvent)
{
	CameraMoveEvent* CameraMove = static_cast<CameraMoveEvent*>(pEvent);

	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));

	float
		L = CameraMove->currentPos.x - CameraMove->SCR_WIDTH / 2.f,
		R = CameraMove->currentPos.x + CameraMove->SCR_WIDTH / 2.f,
		U = CameraMove->currentPos.y + CameraMove->SCR_HEIGHT / 2.f,
		B = CameraMove->currentPos.y - CameraMove->SCR_HEIGHT / 2.f;


	if (pTr->mPosition.x > L && pTr->mPosition.x < R && pTr->mPosition.y < U && pTr->mPosition.y > B)
		isAwake = true;
	else
		isAwake = false;
}
