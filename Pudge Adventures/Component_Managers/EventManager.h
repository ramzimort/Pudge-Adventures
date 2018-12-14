#pragma once

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: EventManger.h
Purpose: Stores event subscribers and broadcasts them when invoked. Also manages timed events. Can broadcast to all objects
Language: C/C++
Platform: Windows 10
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/


#include <list>
#include <unordered_map>


class GameObject;
class Event;
enum EventType;

class EventManager
{
	public:
		EventManager();
		~EventManager();
		void Update();

		void BroadcastEvent(Event* pEvent);
		void BroadcaseEventToSubscribers(Event* pEvent);
		void AddTimeEvent(Event* pEvent);
		void Subscribe(EventType type, GameObject* pGameObject);
		void Unsubscribe(EventType type, GameObject* pGameObject);
		void ForceTimedEvent(EventType type);
	
public:
		std::list<Event*> mTimedEvents;
		std::unordered_map<EventType, std::list<GameObject*>> mSubscriptions;

};