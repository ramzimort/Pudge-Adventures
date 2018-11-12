#pragma once

enum EventType
{
	COLLIDE,
	INVOKE_HOOK,
	CAMERA_MOVE,
	PLAYER_MOVE,
	ROTATE_ARM_TOWARD_POINTER,
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
