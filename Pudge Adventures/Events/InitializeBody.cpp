
#include "InitializeBody.h"

InitializeBodyEvent::InitializeBodyEvent() : Event(INITIALIZE_BODY),
mScale(0.f),
InitialPosition(0.f),
mPivot(0.f)
{ }

InitializeBodyEvent::~InitializeBodyEvent()
{ }