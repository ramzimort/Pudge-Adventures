
#include "CameraMove.h"

CameraMoveEvent::CameraMoveEvent() : Event(CAMERA_MOVE), deltaX(0.f)
{ }

CameraMoveEvent::~CameraMoveEvent()
{ }