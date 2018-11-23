#pragma once

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