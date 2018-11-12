
#include "RotateArmTowardPointer.h"

RotateArmTowardPointerEvent::RotateArmTowardPointerEvent() :	
	Event(ROTATE_ARM_TOWARD_POINTER),
	pointerPos(0.0f),
	cameraCenter(0.0f),
	SCR_WIDTH(0),
	SCR_HEIGHT(0)
{ }

RotateArmTowardPointerEvent::~RotateArmTowardPointerEvent()
{ }