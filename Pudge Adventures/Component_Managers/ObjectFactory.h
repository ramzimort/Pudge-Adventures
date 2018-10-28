#pragma once

#include <string>

class GameObject;

class ObjectFactory {
	public:
		ObjectFactory();
		~ObjectFactory();

		void LoadLevel(std::string& pFileName);
		GameObject* LoadObject(std::string& pFileName);
		
};