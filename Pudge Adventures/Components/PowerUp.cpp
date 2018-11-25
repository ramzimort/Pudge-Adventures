
#include "PowerUp.h"

PowerUp::PowerUp() :
	Component(POWERUP)
{ }
PowerUp::~PowerUp() { }

void PowerUp::Init()
{ }

void PowerUp::Update()
{ }

void PowerUp::Serialize(rapidjson::Document& objFile)
{
	std::string type = objFile["PowerUp"].GetString();
	if (type == "DD")
		mType = DD;
	else if (type == "Regen")
		mType = REGEN;
	else if (type == "Haste")
		mType = HASTE;
}

void PowerUp::HandleEvent(Event* pEvent)
{ }