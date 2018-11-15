#pragma once

enum EventType
{
	INITIALIZE_BODY,
	SCALE_BODY,
	UPDATE_BODY,
	UPDATE_POSITION,
	MIRROR_OBJECT,
	CAMERA_MOVE,
	INVOKE_HOOK,
	PLAYER_MOVE,
	ROTATE_ARM_TOWARD_POINTER,
	PLAYER_HIT,
	COLLIDE,
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
