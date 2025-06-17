#pragma once

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <stdexcept>
#include "EntityManager.h"

class IComponentArray {
public:
	virtual ~IComponentArray() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
public:
	void insertData(Entity entity, T component) {
		entityToComponent[entity] = component;
	}

	void removeData(Entity entity) {
		entityToComponent.erase(entity);
	}

	T& getData(Entity entity) {
		return entityToComponent.at(entity);
	}

	void entityDestroyed(Entity entity) override {
		removeData(entity);
	}

private:
	std::unordered_map<Entity, T> entityToComponent;
};

class ComponentManager {
public:
	template<typename T>
	void addComponent(Entity entity, T component) {
		getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity) {
		getComponentArray<T>()->removeData(entity);
	}

	template<typename T>
	T& getComponent(Entity entity) {
		return getComponentArray<T>()->getData(entity);
	}

	void entityDestroyed(Entity entity) {
		for (auto const& pair : componentArrays) {
			pair.second->entityDestroyed(entity);
		}
	}

private:
	std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;

	template<typename T>
	ComponentArray<T>* getComponentArray() {
		std::type_index typeIndex(typeid(T));
		if (componentArrays.find(typeIndex) == componentArrays.end()) {
			componentArrays[typeIndex] = std::make_unique<ComponentArray<T>>();
		}
		return static_cast<ComponentArray<T>*>(componentArrays[typeIndex].get());
	}
};