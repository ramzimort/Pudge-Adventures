
#include "MirrorObject.h"

MirrorObjectEvent::MirrorObjectEvent() : 
	Event (MIRROR_OBJECT),
	isMirror(false)
{ }

MirrorObjectEvent::~MirrorObjectEvent()
{ }