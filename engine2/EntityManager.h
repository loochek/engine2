#pragma once

#include <queue>
#include <array>
#include "Entity.h"

class EntityManager
{
public:
	EntityManager();
	Entity create();
	void destroy(Entity entity);
	void setSignature(Entity entity, Signature signature);
	Signature getSignature(Entity entity);

private:
	std::queue<Entity> mAvailableEntities;
	std::array<Signature, MAX_ENTITIES> mSignatures;
};