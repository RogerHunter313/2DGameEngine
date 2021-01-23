#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;	//https://www.geeksforgeeks.org/what-are-forward-declarations-in-c/
class EntityManager;

class Entity {
	public:
		std::string name;
		Entity(EntityManager& manager);
		Entity(EntityManager& manager, std::string name);
		void Update(float deltaTime);
		void Render();
		void Destroy();
		bool IsActive() const;

	private:
		EntityManager& manager;
		bool isActive;
		std::vector<Component*> components;
};

#endif
