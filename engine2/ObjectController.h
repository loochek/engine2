#pragma once

#include <memory>
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class ObjectController
{
public:
	static ObjectController& getInstance()
	{
		static ObjectController singleton;
		return singleton;
	}

	Entity createEntity()
	{
		return mEntityManager.create();
	}

	void destroyEntity(Entity entity)
	{
		mEntityManager.destroy(entity);
		mComponentManager.entityDestroyed(entity);
		mSystemManager.entityDestroyed(entity);
	}

	template<typename T>
	void registerComponent()
	{
		mComponentManager.registerComponent<T>();
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		mComponentManager.addComponent(entity, component);

		Signature signature = mEntityManager.getSignature(entity);
		signature.set(mComponentManager.getComponentID<T>(), true);
		mEntityManager.setSignature(entity, signature);

		mSystemManager.entitySignatureChanged(entity, signature);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		mComponentManager.removeComponent(entity);

		Signature signature = mEntityManager.getSignature(entity);
		signature.set(mComponentManager.getComponentID(), false);
		mEntityManager.setSignature(entity, signature);

		mSystemManager.entitySignatureChanged(entity, signature);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return mComponentManager.getComponent<T>(entity);
	}

	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		return mSystemManager.registerSystem<T>();
	}

	template<typename system, typename component>
	void setSystemRequirement(bool need)
	{
		Signature signature = mSystemManager.getSignature<system>();
		signature.set(mComponentManager.getComponentID<component>(), need);
		mSystemManager.setSignature<system>(signature);
	}

private:
	EntityManager mEntityManager;
	ComponentManager mComponentManager;
	SystemManager mSystemManager;

	template<typename T>
	void setSystemSignature(Signature signature)
	{
		mSystemManager.setSignature(signature);
	}

	ObjectController() {}                                      // Private constructor
	~ObjectController() {}
	ObjectController(const ObjectController&);                 // Prevent copy-construction
	ObjectController& operator=(const ObjectController&);      // Prevent assignment
};