#include "GameObject.h"
#include "Transform.h"
#include "Sprite.h"
#include "Controller.h"
#include "Body.h"
#include "AI.h"
#include "Arms.h"
#include "Camera.h"
#include "Obstacle.h"

GameObject::GameObject()
{
}


GameObject::~GameObject() {
	for (auto c : mComponents)
		delete c;
	mComponents.clear();
}

void GameObject::Init()
{
	for (auto c : mComponents)
		c->Init();
}

void GameObject::Update() {
	for (auto c : mComponents)
		c->Update();
}

Component* GameObject::AddComponent(unsigned int Type) {
	Component* pNewComponent = nullptr;
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
	case BOTAI:
		pNewComponent = new botAI();
		break;
	case BODY:
		pNewComponent = new Body();
		break;
	case ARMS:
		pNewComponent = new Arms();
		break;
	case CAMERA:
		pNewComponent = new Camera();
		break;
	case OBSTACLE:
		pNewComponent = new Obstacle();
		break;
	}

	if (pNewComponent != nullptr) {
		mComponents.push_back(pNewComponent);
		pNewComponent->mpOwner = this;
	}
	return pNewComponent;
}

Component* GameObject::GetComponent(unsigned int Type) const{
	for (auto c : mComponents)
		if (c->getType() == Type)
			return c;

	return nullptr;
}

bool GameObject::HasComponent(unsigned int Type) const {
	for (auto c : mComponents)
		if (c->getType() == Type)
			return true;
	return false;
}

void GameObject::HandleEvent(Event * pEvent)
{
	for (auto c : mComponents)
	{
		c->HandleEvent(pEvent);
	}
}
