#pragma once


class GameObject;

class Controller {
	Controller();
	~Controller();

	void Update();

	GameObject* mpOwner;
};