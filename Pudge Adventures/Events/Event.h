#pragma once

enum EventType
{
	COLLIDE,
	CAMERA_MOVE,
	PLAYER_MOVE,
	ROTATE_ARM,
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
