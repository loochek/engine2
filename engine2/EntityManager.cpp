#include "EntityManager.h"

EntityManager::EntityManager()
{
	for (size_t i = 0; i < MAX_ENTITIES; i++)
		mAvailableEntities.push(i);
}

Entity EntityManager::create()
{
	Entity entity = mAvailableEntities.front();
	mAvailableEntities.pop();
	return entity;
}

void EntityManager::destroy(Entity entity)
{
	mAvailableEntities.push(entity);
}

void EntityManager::setSignature(Entity entity, Signature signature)
{
	mSignatures[entity] = signature;
}

Signature EntityManager::getSignature(Entity entity)
{
	return mSignatures[entity];
}
