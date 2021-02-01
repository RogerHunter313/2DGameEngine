#include "EntityManager.h"
#include <iostream>
#include "ColliderComponent.h"
#include "Component.h"
#include "Collision.h"

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

void EntityManager::Render() {  //TODO:: can optimize how layers are accessed
	for (int layerNumber = 0; layerNumber <= NUM_LAYERS; layerNumber++) {
		for (auto& entity : GetEntitiesByLayer(static_cast<LayerType>(layerNumber))) {
			entity->Render();
		}
	}
	
	//for (auto& entity : entities) {  //code when only one layer existed
	//	entity->Render();
	//}
}

std::vector<Entity*> EntityManager::GetEntitiesByLayer(LayerType layer) const {
	std::vector<Entity*> selectedEntities;
	for (auto& entity : entities) {
		if (entity->layer == layer) {
			selectedEntities.emplace_back(entity);
		}
	}
	return selectedEntities;		//TODO: the nested for loops can be improved
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

std::string EntityManager::CheckEntityCollisions(Entity& myEntity) const {
	ColliderComponent* myCollider = myEntity.GetComponent<ColliderComponent>();
	for (auto& entity : entities) {
		if (entity->name.compare(myEntity.name) != 0 && entity->name.compare("Tile")) {
			if (entity->HasComponent<ColliderComponent>()) {
				ColliderComponent* otherCollider = entity->GetComponent<ColliderComponent>();
				if (Collision::CheckRectangleCollision(myCollider->collider, otherCollider->collider)) {
					return otherCollider->colliderTag;
				}
			}
		}
	}
	return std::string();  //return empty string if no collisions found
}

bool EntityManager::HasNoEntities() {
	return entities.size() == 0;
}

Entity& EntityManager::AddEntity(std::string entityName, LayerType layer) {
	Entity* entity = new Entity(*this, entityName, layer);
	entities.emplace_back(entity);
	return *entity;
}

std::vector<Entity*> EntityManager::GetEntities() const {
	return entities;
}
unsigned int EntityManager::GetEntityCount() {
	return entities.size();
}