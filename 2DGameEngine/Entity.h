#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <string>
#include <typeinfo>
#include <map>
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
		std::string GetName() const;

		template <typename T, typename... TArgs>
		T& AddComponent(TArgs&&... args) {
			T* newComponent(new T(std::forward<TArgs>(args)...));
			newComponent->owner = this;
			components.emplace_back(newComponent);  //https://stackoverflow.com/questions/10890653/why-would-i-ever-use-push-back-instead-of-emplace-back
			componentTypeMap[&typeid(*newComponent)] = newComponent;  //complete a map based on type
			newComponent->Initialize();
			return *newComponent;
		}

		template <typename T>
		T* GetComponent() {
			return static_cast<T*>(componentTypeMap[&typeid(T)]);
		}

	private:
		EntityManager& manager;
		bool isActive;
		std::vector<Component*> components;
		std::map<const std::type_info*, Component*> componentTypeMap;
};

#endif
