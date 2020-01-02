#pragma once

#include <cassert>
#include <stdint.h>
#include <vector>
#include <unordered_map>
#include "Entity.h"


// Used for component store templates generalization
class IComponentStore
{
public:
	virtual ~IComponentStore() = default;
	virtual void entityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentStore : public IComponentStore
{
public:
	void add(Entity entity, T component)
	{
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once");
		// Put new element at end and update links
		mComponents[mSize] = component;
		mEntityToIndexMap[entity] = mSize;
		mIndexToEntityMap[mSize] = entity;
		mSize++;
	}

	void remove(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component");
		// Copy last element into deleted element's place to maintain density
		size_t removedEntityIndex = mEntityToIndexMap[entity];
		mComponents[removedEntityIndex] = mComponents[mSize - 1];
		// Update links
		mEntityToIndexMap[mIndexToEntityMap[mSize - 1]] = removedEntityIndex;
		mIndexToEntityMap[removedEntityIndex] = mIndexToEntityMap[mSize - 1];
		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(mSize - 1);

		mSize--;
	}

	T& get(Entity entity)
	{
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component");
		return mComponents[mEntityToIndexMap[entity]];
	}

	bool hasComponent(Entity entity)
	{
		return mEntityToIndexMap.find(entity) != mEntityToIndexMap.end();
	}

	virtual void entityDestroyed(Entity entity) override
	{
		remove(entity);
	}

private:
	std::array<T, MAX_ENTITIES> mComponents;
	std::unordered_map<Entity, size_t> mEntityToIndexMap;
	std::unordered_map<size_t, Entity> mIndexToEntityMap;
	size_t mSize;
};