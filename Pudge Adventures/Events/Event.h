#pragma once

enum EventType
{
	INITIALIZE_BODY,
	SCALE_BODY,
	ROTATE_BODY,
	UPDATE_BODY,
	UPDATE_POSITION,
	MIRROR_OBJECT,
	MIRROR_ARM,
	CAMERA_MOVE,
	INVOKE_HOOK,
	PLAYER_MOVE,
	ROTATE_TOWARD_POINTER,
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
