#include "Camera.h"
#include "Body.h"
#include "..\Component_Managers\GraphicsManager.h"
#include "..\Component_Managers\EventManager.h"
#include "..\Events\InvokeHook.h"
#include "..\Events\RotateArmTowardPointer.h"

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
	mCameraCenter = static_cast<Body*>(mpOwner->GetComponent(BODY))->mPos;
}

void Camera::Update()
{
	glm::vec2 bodyCurrentPos = static_cast<Body*>(mpOwner->GetComponent(BODY))->mPos;
	glm::vec2 deltaCameraPos = bodyCurrentPos - (mCameraCenter + glm::vec2(rightBound,upperBound));
	if (bodyCurrentPos.x > mCameraCenter.x + rightBound)
		mCameraCenter.x += deltaCameraPos.x;
	if (bodyCurrentPos.y > mCameraCenter.y + upperBound)
		mCameraCenter.y += deltaCameraPos.y;
}

void Camera::HandleEvent(Event* pEvent)
{
	if (pEvent->mType == INVOKE_HOOK)
	{
		InvokeHookEvent* invokeHook = static_cast<InvokeHookEvent*>(pEvent);
		
		RotateArmTowardPointerEvent RATPe;
		RATPe.pointerPos = invokeHook->pointerPos;
		RATPe.cameraCenter = mCameraCenter;
		RATPe.SCR_WIDTH = gpGfxManager->getWindowWidth();
		RATPe.SCR_HEIGHT = gpGfxManager->getWindowHeight();
		gpEventManager->BroadcaseEventToSubscribers(&RATPe);
	}
}

void Camera::Serialize(rapidjson::Document& objectFile)
{

}