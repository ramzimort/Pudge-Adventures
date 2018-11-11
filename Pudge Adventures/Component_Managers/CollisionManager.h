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
												std::list<Contact*> &Contacts);

	public:
		std::list<Contact*> mContacts;

		bool(*CollisionFunctions[2][2])(Shape* pShape1,
										Shape* pShape2,
										std::list<Contact*> &Contacts);
};