#pragma once

enum EventType
{
	MOVE_LEFT,
	MOVE_RIGHT,
	JUMP,
	BLOCK_MOVE,
	UNBLOCK_MOVE,

	UPDATE_POSITION,
	SET_ANGLE,
	UPDATE_BODY,
	ROTATE_BODY,
	MIRROR_OBJECT,

	INVOKE_CLEAVE,
	INVOKE_HOOK,
	RETURN_HOOK,
	GRAB_HOOK,

	CAMERA_MOVE,
	UPDATE_MOUSE_SCREEN_POSITION,
	UPDATE_MOUSE_WORLD_POSITION,

	NUM
};

class Event
{
public:
	Event(EventType Type) : mType(Type), mTimer(0.f) { }
	virtual ~Event() { }

public:
	EventType mType;
	float mTimer;
};
