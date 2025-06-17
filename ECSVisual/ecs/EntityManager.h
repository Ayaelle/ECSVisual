#pragma once

#include <queue>
#include <set>
#include <cstdint>
#include <stdexcept>

using Entity = std::uint32_t;
const Entity MAX_ENTITIES = 5000;

class EntityManager {
public:
	EntityManager()
	{
		for (Entity entity = 0; entity < MAX_ENTITIES; entity++)
		{
			availableEntities.push(entity);
		}
	}

	Entity createEntity() {
		if (livingEntityCount >= MAX_ENTITIES)
			throw std::runtime_error("Too many entities in existence.");

		Entity id = availableEntities.front();
		availableEntities.pop();
		livingEntityCount++;
		activeEntities.insert(id);
		return id;
	}

	void destroyEntity(Entity entity) {
		activeEntities.erase(entity);
		availableEntities.push(entity);
		livingEntityCount--;
	}

	bool isAlive(Entity entity) const {
		return activeEntities.find(entity) != activeEntities.end();
	}

private:
	std::queue<Entity> availableEntities;
	std::set<Entity> activeEntities;
	std::uint32_t livingEntityCount = 0;
};