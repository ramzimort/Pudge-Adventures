

#include "botAI3.h"
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

botAI3::botAI3() :
	Component(BOTAI3),
	CurrentTime(0.f),
	AttackSpeed(0.f),
	ProjectileName(""),
	ProjectileSpeed(0.f),
	isAwake(false),
	Shooter_Pudge(0.f)
{ }

botAI3::~botAI3()
{

}

void botAI3::Init()
{
	isAwake = false;
	gpEventManager->Subscribe(UPDATE_POSITION, mpOwner);
	gpEventManager->Subscribe(CAMERA_MOVE, mpOwner);
	gpEventManager->Subscribe(JUKE, mpOwner);
	CurrentTime = AttackSpeed;

	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	pBody->mVel.x = 0.f;

}

void botAI3::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["AI3"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "MoveSpeed")
			MoveSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "AttackSpeed")
			AttackSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "ProjectileSpeed")
			ProjectileSpeed = ComponentValues.value.GetFloat();
		else if (componentValueName == "ProjectileOffset")
			ProjectileOffset = glm::vec2(ComponentValues.value.GetArray()[0].GetFloat(), ComponentValues.value.GetArray()[1].GetFloat());
		else if (componentValueName == "Projectile")
			ProjectileName = ComponentValues.value.GetString();
	}
}

void botAI3::Update()
{
	
	if (isAwake)
	{
		Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
		Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
		if (pBody->mVel.x == 0.f)
			pBody->mVel.x = MoveSpeed;
		
		if (pTr->mPosition.x < camLeft)
			pBody->mVel.x = MoveSpeed;
		else if (pTr->mPosition.x > camRight)
			pBody->mVel.x = -1.f*MoveSpeed;


		static_cast<Sprite*>(mpOwner->GetComponent(SPRITE))->enableAnimation = true;
		CurrentTime -= gpFRC->GetFrameTime();
		if (CurrentTime < 0.f)
		{
			CurrentTime = AttackSpeed;
			ShootProjectile();
		}
	}
}

void botAI3::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case UPDATE_POSITION:
	{
		Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
		glm::vec2 PudgePos = static_cast<UpdatePositionEvent*>(pEvent)->newPosition;
		Shooter_Pudge = PudgePos - (pTr->mPosition+ProjectileOffset);
		float newAngle = findAcuteAngle(glm::vec2(0.f, 1.f), Shooter_Pudge);

		if (pTr->mPosition.y - PudgePos.y < 200)
			static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel.y = MoveSpeed;
		else if((pTr->mPosition.y - PudgePos.y > 500))
			static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel.y = -1.f * MoveSpeed;
		break;
	}
	case CAMERA_MOVE:
		CheckCamera(pEvent);
		break;
	case JUKE:
		static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel.x *= -1.f;
	}
}

float botAI3::findAcuteAngle(glm::vec2 const& V1, glm::vec2 const& V2)
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

void botAI3::ShootProjectile()
{
	GameObject* projectile = gpObjectFactory->LoadObject(ProjectileName);
		Transform* pTr = static_cast<Transform*>(projectile->GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(projectile->GetComponent(BODY));
	if (pTr != nullptr && pBody!= nullptr)
	{
		pTr->mPosition = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition + ProjectileOffset;
		projectile->Init();
		pBody->mVel = glm::normalize(Shooter_Pudge)*ProjectileSpeed;
	}
}

void botAI3::CheckCamera(Event* pEvent)
{
	CameraMoveEvent* CameraMove = static_cast<CameraMoveEvent*>(pEvent);

	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));

	float
		L = CameraMove->currentPos.x - CameraMove->SCR_WIDTH / 2.f,
		R = CameraMove->currentPos.x + CameraMove->SCR_WIDTH / 2.f,
		U = CameraMove->currentPos.y + CameraMove->SCR_HEIGHT / 2.f,
		B = CameraMove->currentPos.y - CameraMove->SCR_HEIGHT / 2.f;


	if (pTr->mPosition.x > L && pTr->mPosition.x < R && pTr->mPosition.y < U && pTr->mPosition.y > B)
	{
		isAwake = true;
		camLeft = L;
		camRight = R;
	}

}
