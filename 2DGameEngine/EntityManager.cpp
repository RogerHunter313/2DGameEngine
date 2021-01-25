#include "EntityManager.h"
#include <iostream>

void EntityManager::ClearData() {
	for (auto& entity : entities) {
		entity->Destroy();
	}
}

void EntityManager::Update(float deltaTime) {
	for (auto& entity : entities) {
		entity->Update(deltaTime);
	}
}

void EntityManager::Render() {
	for (auto& entity : entities) {
		entity->Render();
	}
}

void EntityManager::ListAllEntities() const{

	unsigned int i = 0;  //keep track of the number of entities

	for (auto& entity : entities) {
		std::cout << "Entity ["<< i << "] = " << entity->GetName() << std::endl;
		
		entity->ListAllComponents();

		std::cout << std::endl;
		i++;
	}
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName) {
	Entity* entity = new Entity(*this, entityName);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}
unsigned int EntityManager::GetEntityCount() {
	return entities.size();
}