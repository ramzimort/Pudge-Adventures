#include "Camera.h"
#include "Transform.h"
#include "..\Component_Managers\GraphicsManager.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\InvokeHook.h"
#include "..\Events\RotateTowardPointer.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\CameraMove.h"
#include "..\Events\UpdateMouseScreenPosition.h"
#include "..\Events\UpdateMouseWorldPosition.h"
#include <iostream>

extern GraphicsManager* gpGfxManager;
extern EventManager* gpEventManager;

Camera::Camera():	Component(CAMERA),
					mCameraCenter(0.0f),
					rightBound(0.0f),
					upperBound(0.0f)
{ }

Camera::~Camera()
{ }

void Camera::Init()
{
	rightBound = (float)gpGfxManager->getWindowWidth() / 4.0f;
	upperBound = 0;

	//upperBound = (float)gpGfxManager->getWindowHeight() / 4.0f;
	
	Transform* pTr = static_cast<Transform*>(mpOwner->GetComponent(TRANSFORM));
	if(pTr != nullptr)
		mCameraCenter = pTr->mPosition;
}

void Camera::Update()
{ }

void Camera::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case UPDATE_POSITION:
	{
		glm::vec2 bodyCurrentPos = static_cast<UpdatePositionEvent*>(pEvent)->newPosition;
		glm::vec2 deltaCameraPos = bodyCurrentPos - (mCameraCenter + glm::vec2(rightBound, upperBound));
		if (bodyCurrentPos.x > mCameraCenter.x + rightBound)
		{
			mCameraCenter.x += deltaCameraPos.x;
			CameraMoveEvent CameraMove;
			CameraMove.deltaX = deltaCameraPos.x;
			gpEventManager->BroadcaseEventToSubscribers(&CameraMove);
		}
		mCameraCenter.y = bodyCurrentPos.y;
		if (mCameraCenter.y < 100.f)
			mCameraCenter.y = 100.f;
		break;
	}
	case UPDATE_MOUSE_SCREEN_POSITION:
		UpdateMousePosWorldSpace(static_cast<UpdateMouseScreenPositionEvent*>(pEvent)->MouseScreenPosition);
		break;
	}
}

void Camera::Serialize(rapidjson::Document& objectFile)
{
}

void Camera::UpdateMousePosWorldSpace(glm::vec2& MouseScreenPosition)
{
	glm::vec2 cameraPosWorldSpace = MouseScreenPosition + mCameraCenter;
	cameraPosWorldSpace.x -= (float)gpGfxManager->getWindowWidth() / 2.f;
	cameraPosWorldSpace.y -= (float)gpGfxManager->getWindowHeight() / 2.f;
	UpdateMouseWorldPositionEvent UpdateMouseWorldPos(cameraPosWorldSpace);
	mpOwner->HandleEvent(&UpdateMouseWorldPos);
}