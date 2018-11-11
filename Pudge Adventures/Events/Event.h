#pragma once

enum EventType
{
	COLLIDE,
	PLAYER_INPUT,
	PLAYER_HIT,
	NUM
};

class Event
{
public:
	Event(EventType Type);
	virtual ~Event() {}

	EventType mType;
	float mTimer;
};
