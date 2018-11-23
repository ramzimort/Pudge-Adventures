
#include "Background.h"
#include "GameObject.h"
#include "Transform.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\CameraMove.h"
#include "..\Events\UpdatePosition.h"

extern EventManager* gpEventManager;

Background::Background() : 
	Component(BACKGROUND), 
	scrollingSpeed(0.f),
	mPos(0.0f)
{ }

Background::~Background()
{ }

void Background::Init()
{ 
	gpEventManager->Subscribe(CAMERA_MOVE, mpOwner);
	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	mPos = pTr->mPosition;
}

void Background::Update()
{ 
	UpdatePositionEvent UpdatePosition;
	UpdatePosition.newPosition = mPos;
	mpOwner->HandleEvent(&UpdatePosition);
}

void Background::HandleEvent(Event* pEvent)
{ 
	switch (pEvent->mType)
	{
	case CAMERA_MOVE:
		mPos.x -= static_cast<CameraMoveEvent*>(pEvent)->deltaX*scrollingSpeed;
		break;
	}
}

void Background::Serialize(rapidjson::Document& objectFile)
{ 
	std::string componentValueName;
	for (auto& ComponentValues : objectFile["Background"].GetObject())
	{
		componentValueName = ComponentValues.name.GetString();
		if (componentValueName == "Scroll_Speed")
			scrollingSpeed = ComponentValues.value.GetFloat();
	}
}