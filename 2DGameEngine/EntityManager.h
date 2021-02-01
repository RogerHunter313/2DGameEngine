#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "Entity.h"
#include "Component.h"
#include "Constants.h"

class EntityManager {
	public:
		void ClearData();
		void Update(float deltaTime);
		void Render();
		void ListAllEntities() const;
		bool HasNoEntities();
		Entity& AddEntity(std::string entityName, LayerType layer);
		std::vector<Entity*> GetEntities() const;
		std::vector<Entity*> GetEntitiesByLayer(LayerType layer) const;
		unsigned int GetEntityCount();
		std::string CheckEntityCollisions(Entity& entity) const;

	private:
		std::vector<Entity*> entities;
};

#endif
