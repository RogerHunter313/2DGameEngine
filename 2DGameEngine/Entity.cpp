#include "Entity.h"
															//https://www.geeksforgeeks.org/when-do-we-use-initializer-list-in-c/
Entity::Entity(EntityManager& manager) : manager(manager) {  //constructor instantiates the manager right here after : similar to this->
	//this->manager = manager;	//this won't work here https://www.internalpointers.com/post/understanding-meaning-lvalues-and-rvalues-c
	this->isActive = true;
}

Entity::Entity(EntityManager& manager, std::string name) : manager(manager), name(name) {
	this->isActive = true;
}

std::string Entity::GetName() const {
	return name;
}

void Entity::Update(float deltaTime) {
	for (auto& component : components) {
		component->Update(deltaTime);
	}
}

void Entity::Render() {
	for (auto& component : components) {
		component->Render();
	}
}

void Entity::Destroy() {
	this->isActive = false;
}

bool Entity::IsActive() const {
	return this->isActive;
}