
#include "UpdatePosition.h"

UpdatePositionEvent::UpdatePositionEvent() : 
	Event(UPDATE_POSITION),
	newPosition(0.f),
	newAngle(0.f)
{ }
UpdatePositionEvent::~UpdatePositionEvent()
{ }