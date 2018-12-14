#pragma once


/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: Event.h
Purpose: Parent class to all events. Some events are inherited to pass data along with invoking an event
Language: C/C++
Platform: Windows 10, MSC_VER:1912
Project: Milestone 1
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

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

	APPLY_DAMAGE,
	JUKE,

	ENABLE_HASTE,
	DISABLE_HASTE,
	ENABLE_DD,
	DISABLE_DD,
	ENABLE_REGEN,
	DISABLE_REGEN,

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
