#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"


/*
GameObject::GameObject()
{
}
*/

GameObject::~GameObject() {
	for (auto c : mComponents)
		delete c;
	mComponents.clear();
}

void GameObject::Update() {
	for (auto c : mComponents)
		c->Update();
}

void GameObject::AddComponent(unsigned int Type) {
	Component* pNewComponent;
	switch (Type) {
	case TRANSFORM:
		pNewComponent = new Transform();
		break;

	case SPRITE:
		pNewComponent = new Sprite();
		break;

	case CONTROLLER:
		pNewComponent = new Controller();
		break;
	}

	if (pNewComponent != nullptr) {
		mComponents.push_back(pNewComponent);
		pNewComponent->mpOwner = this;
	}
}

Component* GameObject::GetComponent(unsigned int Type) {
	for (auto c : mComponents)
		if (c->getType() == Type)
			return c;

	return nullptr;
}