
#include "Component.h"

Component::Component(unsigned int Type) 
{
	mType = Type;
}

unsigned int Component::getType() 
{
	return mType;
}