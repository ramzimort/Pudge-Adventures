
#include "RotateTowardPointer.h"

RotateTowardPointerEvent::RotateTowardPointerEvent() :
	Event(ROTATE_TOWARD_POINTER),
	PointerPositonWorldSpace(0.f)
{ }
RotateTowardPointerEvent::~RotateTowardPointerEvent()
{ }