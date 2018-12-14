#pragma once

/* Start Header -------------------------------------------------------
Copyright (C) 2018 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
File Name: CollisionManager.h
Purpose: Handles all collision checks between object shapes (AABB or CIRCLE)
Language: C/C++
Platform: Windows 10
Project: CS_529_FinalProject
Author: Ramzi Mourtada, ramzi.mourtada, 60001618
Creation date: 12/13/2018
- End Header --------------------------------------------------------*/

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