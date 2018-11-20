#include "Camera.h"
#include "..\Component_Managers\GraphicsManager.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\InitializeBody.h"
#include "..\Events\InvokeHook.h"
#include "..\Events\RotateTowardPointer.h"
#include "..\Events\UpdatePosition.h"
#include "..\Events\CameraMove.h"
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
}

void Camera::Update()
{ }

void Camera::HandleEvent(Event* pEvent)
{
	switch (pEvent->mType)
	{
	case INITIALIZE_BODY:
		mCameraCenter = static_cast<InitializeBodyEvent*>(pEvent)->InitialPosition;
		break;
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
	case INVOKE_HOOK:
		InvokeHookEvent* invokeHook = static_cast<InvokeHookEvent*>(pEvent);
		RotateTowardPointerEvent RTPe;
		glm::vec2 cameraPosWorldSpace = invokeHook->pointerPos + mCameraCenter;
		cameraPosWorldSpace.x -= (float)gpGfxManager->getWindowWidth() / 2.f;
		cameraPosWorldSpace.y -= (float)gpGfxManager->getWindowHeight() / 2.f;
		RTPe.PointerPositonWorldSpace = cameraPosWorldSpace;
		gpEventManager->BroadcaseEventToSubscribers(&RTPe);
		break;
	}
}

void Camera::Serialize(rapidjson::Document& objectFile)
{

}