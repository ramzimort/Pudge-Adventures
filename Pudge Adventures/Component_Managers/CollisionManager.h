#pragma once

#include <list>

#include <glm/glm.hpp>

class Body;
class Shape;




class Contact
{	
	public:
		Body* mBodies[2];

	public:
		Contact();
		~Contact();
};

class CollisionManager
{
	public:
		CollisionManager();
		~CollisionManager();

		void Reset();
		bool checkCollisionandGenerateContact(	Shape* pShape1,
												Shape* pShape2,
			std::list<std::pair<Contact*, glm::vec2>> &Contacts);

	public:
		std::list<std::pair<Contact*, glm::vec2>> mContacts;

		bool(*CollisionFunctions[2][2])(Shape* pShape1,
										Shape* pShape2,
			std::list<std::pair<Contact*, glm::vec2>> &Contacts);
};