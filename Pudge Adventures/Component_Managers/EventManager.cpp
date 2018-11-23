#include "EventManager.h"
#include "GameObjectManager.h"
#include "FrameRateController.h"
#include "..\Events\Event.h"
#include "..\Components\GameObject.h"

extern GameObjectManager* gpGameObjectManager;
extern FrameRateController* gpFRC;


EventManager::EventManager()
{

}

EventManager::~EventManager()
{
	auto it = mTimedEvents.begin();
	while (it != mTimedEvents.end())
	{
		Event* pEvent = *it;
		delete pEvent;
	}
}

void EventManager::Update()
{
	// Loop through all timed events
	// Decrease timer by FramTiem
	// <0 ? FIRE EVENT
	auto it = mTimedEvents.begin();
	while (it != mTimedEvents.end())
	{
		Event* pEvent = *it;
		pEvent->mTimer -= gpFRC->GetFrameTime();
		if (pEvent->mTimer <= 0.0f)
		{
			BroadcaseEventToSubscribers(pEvent);
			delete pEvent;
			it = mTimedEvents.erase(it);
		}
		else
			++it;
	}
}

void EventManager::BroadcastEvent(Event * pEvent)
{
	for (auto go : gpGameObjectManager->mGameObjects)
	{
		go->HandleEvent(pEvent);
	}
}

void EventManager::BroadcaseEventToSubscribers(Event * pEvent)
{
	auto &listofSubscribers = mSubscriptions[pEvent->mType];
	for (auto pGO : listofSubscribers)
		pGO->HandleEvent(pEvent);
}

void EventManager::AddTimeEvent(Event * pEvent)
{
	mTimedEvents.push_back(pEvent);
}

void EventManager::Subscribe(EventType type, GameObject * pGameObject)
{
	std::list<GameObject*> &listofSubscribers = mSubscriptions[type];
	for (GameObject* pGO : listofSubscribers)
	{
		if (pGO == pGameObject)
			return;	
	}
	listofSubscribers.push_back(pGameObject);
}

void EventManager::Unsubscribe(EventType type, GameObject * pGameObject)
{
	std::list<GameObject*> &listofSubscribers = mSubscriptions[type];
	for (GameObject* pGO : listofSubscribers)
	{
		if (pGO == pGameObject)
			listofSubscribers.remove(pGameObject);;
	}
}

void EventManager::ForceTimedEvent(EventType type)
{
	auto it = mTimedEvents.begin();
	while (it != mTimedEvents.end())
	{
		Event* pEvent = *it;
		if (pEvent->mType == type)
		{
			BroadcaseEventToSubscribers(pEvent);
			delete pEvent;
			it = mTimedEvents.erase(it);
		}
		else
			++it;
	}
}