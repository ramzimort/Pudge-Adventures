
#include "Attributes.h"
#include "GameObject.h"
#include "..\Component_Managers\FrameRateController.h"
#include "..\Component_Managers\Resource Manager.h"
#include "..\Component_Managers\GameObjectManager.h"
#include "..\Component_Managers\ObjectFactory.h"
#include "Sprite.h"
#include "..\Events\Event.h"
#include "..\Events\ApplyDamage.h"

extern FrameRateController* gpFRC;
extern ResourceManager* gpResourceManager;
extern GameObjectManager* gpGameObjectManager;
extern ObjectFactory* gpObjectFactory;


Attributes::Attributes() : 
	Component(ATTRIBUTES),
	maxHealth(0.f),
	currentHealth(0.f),
	Damage(0.f),
	Regen(false),
	Haste(false),
	HasteTimer(0.f),
	DD(false),
	DDTimer(0.f),
	BloodSplatter(nullptr),
	BloodSplatterTimer(0.f)
{ }

Attributes::~Attributes()
{ 
	if(BloodSplatter != nullptr)
		gpGameObjectManager->toBeDeleted.push(BloodSplatter);
}

void Attributes::Init()
{
	std::string textureName;
	textureName = "HP1.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "HP2.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "HP3.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "HP4.png";
	healthBar = gpResourceManager->LoadTexture(textureName);

	textureName = "DD1.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "DD2.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "DD3.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "DD4.png";
	healthBar = gpResourceManager->LoadTexture(textureName);

	textureName = "Haste1.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "Haste2.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "Haste3.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	textureName = "Haste4.png";
	healthBar = gpResourceManager->LoadTexture(textureName);
	currentHealth = maxHealth;
}

void Attributes::Update()
{
	if (Haste)
	{
		HasteTimer -= gpFRC->GetFrameTime();
		if (HasteTimer <= 0.f)
			mpOwner->HandleEvent(&Event(DISABLE_HASTE));
	}
	if (DD)
	{
		DDTimer -= gpFRC->GetFrameTime();
		if (DDTimer <= 0.f)
			mpOwner->HandleEvent(&Event(DISABLE_DD));
	}
	if (Regen)
	{
		currentHealth = maxHealth;
		Regen = false;
	}
	UpdateHealthBar();
	UpdateDDBar();
	UpdateHasteBar();

	if (currentHealth < 0.f)
		gpGameObjectManager->toBeDeleted.push(mpOwner);
	if (BloodSplatter != nullptr)
	{
		BloodSplatterTimer -= gpFRC->GetFrameTime();
		if (BloodSplatterTimer <= 0.f)
		{
			gpGameObjectManager->toBeDeleted.push(BloodSplatter);
			BloodSplatter = nullptr;
		}
	}
}

void Attributes::Serialize(rapidjson::Document& objectFile)
{
	std::string componentValueName;
	for (auto& componenentValues : objectFile["Attributes"].GetObject())
	{
		componentValueName = componenentValues.name.GetString();
		if (componentValueName == "HP")
			maxHealth = componenentValues.value.GetFloat();
		else if (componentValueName == "Damage")
			Damage = componenentValues.value.GetFloat();
		else if (componentValueName == "RuneTime")
			RuneEffectTime = componenentValues.value.GetFloat();
		else if (componentValueName == "BloodSplatterTime")
			BloodSplatterTime = componenentValues.value.GetFloat();
	}
}

void Attributes::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case ENABLE_HASTE:
		Haste = true;
		HasteTimer = RuneEffectTime;
		break;
	case DISABLE_HASTE:
		Haste = false;
		HasteTimer = 0.f;
		break;
	case ENABLE_DD:
		DD = true;
		DDTimer = RuneEffectTime;
		Damage *= 2.f;
		break;
	case DISABLE_DD:
		DD = false;
		DDTimer = 0.f;
		Damage /= 2.f;
		break;
	case ENABLE_REGEN:
		Regen = true;
		break;
	case DISABLE_REGEN:
		Regen = false;
		break;
	case APPLY_DAMAGE:
		currentHealth -= static_cast<ApplyDamageEvent*>(pEvent)->damage;
		CreateBloodSplatter();
	}
}

void Attributes::UpdateHealthBar()
{
	std::string textureName;
	if (maxHealth == 0.f)
	{
		healthBar = nullptr;
		return;
	}
	if (currentHealth > 0.f && currentHealth <= 0.25*maxHealth)
		textureName = "HP1.png";
	else if (currentHealth > 0.25*maxHealth && currentHealth <= 0.5*maxHealth)
		textureName = "HP2.png";
	else if (currentHealth > 0.5*maxHealth && currentHealth <= 0.75*maxHealth)
		textureName = "HP3.png";
	else if ((currentHealth > 0.75*maxHealth && currentHealth <= maxHealth))
		textureName = "HP4.png";
	else
	{
		healthBar = nullptr;
		return;
	}
	healthBar = gpResourceManager->LoadTexture(textureName);
}

void Attributes::UpdateHasteBar()
{
	std::string textureName;
	if (HasteTimer <= 0.f)
	{
		hasteBar = nullptr;
		return;
	}
	else if (HasteTimer > 0.f && HasteTimer < 0.25*RuneEffectTime)
		textureName = "Haste1.png";
	else if (HasteTimer >= 0.25*RuneEffectTime && HasteTimer < 0.5*RuneEffectTime)
		textureName = "Haste2.png";
	else if (HasteTimer >= 0.5*RuneEffectTime && HasteTimer < 0.75*RuneEffectTime)
		textureName = "Haste3.png";
	else if ((HasteTimer >= 0.75*RuneEffectTime && HasteTimer <= RuneEffectTime))
		textureName = "Haste4.png";
	hasteBar = gpResourceManager->LoadTexture(textureName);
}

void Attributes::UpdateDDBar()
{
	std::string textureName;
	if (DDTimer <= 0.f)
	{
		DDBar = nullptr;
		return;
	}
	else if (DDTimer > 0.f && DDTimer < 0.25*RuneEffectTime)
		textureName = "DD1.png";
	else if (DDTimer >= 0.25*RuneEffectTime && DDTimer < 0.5*RuneEffectTime)
		textureName = "DD2.png";
	else if (DDTimer >= 0.5*RuneEffectTime && DDTimer < 0.75*RuneEffectTime)
		textureName = "DD3.png";
	else if ((DDTimer >= 0.75*RuneEffectTime && DDTimer <= RuneEffectTime))
		textureName = "DD4.png";
	DDBar = gpResourceManager->LoadTexture(textureName);
}

void Attributes::CreateBloodSplatter()
{
	if (BloodSplatter == nullptr)
	{
		BloodSplatter = gpObjectFactory->LoadObject("Blood_Splatter");
		BloodSplatterTimer = BloodSplatterTime;
		Transform* pTr = static_cast<Transform*>(BloodSplatter->GetComponent(TRANSFORM));
		if (pTr != nullptr)
			pTr->mPosition = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM))->mPosition;
		BloodSplatter->Init();
		
		Sprite* pSpr = static_cast<Sprite*>(BloodSplatter->GetComponent(SPRITE));
		if (pSpr != nullptr)
			pSpr->enableAnimation = true;
	}
}