#include "AI.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "Transform.h"
#include "Body.h"
#include "GameObject.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\Event.h"

extern FrameRateController* gpFRC;
extern ObjectFactory* gpObjectFactory;

botAI::botAI() :	
	Component(BOTAI),
	changeDirectionInterval(0.0f),
	currentTime(0.0f) { }

botAI::~botAI() { }

void botAI::Init()
{
	currentTime = changeDirectionInterval;
}

void botAI::Update()
{
	currentTime -= gpFRC->GetFrameTime();
	if (currentTime < 0) 
	{
		speed *= -1.f;
		currentTime = changeDirectionInterval;
		mpOwner->HandleEvent(&Event(MIRROR_OBJECT));
		ShootProjectile();

	}
		
	Body* pBody = static_cast<Body*>(mpOwner->GetComponent(BODY));
	if (pBody != nullptr)
	{
		pBody->mVel.x = -1.f*speed;
	}
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
	}
}

void botAI::HandleEvent(Event * pEvent)
{

}

void botAI::ShootProjectile()
{
	GameObject* projectile = gpObjectFactory->LoadObject(ProjectileName);
	Transform* pTr = static_cast<Transform*>(projectile->GetComponent(TRANSFORM));
	Body* pBody = static_cast<Body*>(projectile->GetComponent(BODY));
	if (pTr != nullptr)
	{
		pTr->mPosition = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition;
		projectile->Init();
		pBody->mVel = static_cast<Body*>(mpOwner->GetComponent(BODY))->mVel*2.f;
	}

}
