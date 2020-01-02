#pragma once

#include <array>
#include "Entity.h"
#include "ComponentStore.h"

class ComponentManager
{
public:
	template<typename T>
	void registerComponent()
	{
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) == mComponentTypes.end() && "Registering component type more than once");
		mComponentStores[mAvailableComponentID] = std::make_shared<ComponentStore<T>>();
		mComponentTypes[typeName] = mAvailableComponentID;
		mAvailableComponentID++;
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		getComponentStore<T>()->add(entity, component);
	}

	template<typename T>
	void removeComponent(Entity entity)
	{
		getComponentStore<T>()->remove(entity);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentStore<T>()->get(entity);
	}

	template<typename T>
	bool hasComponent(Entity entity)
	{
		return getComponentStore<T>()->hasComponent(entity);
	}

	template<typename T>
	ComponentID getComponentID()
	{
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use");
		return mComponentTypes[typeName];
	}

	void entityDestroyed(Entity entity)
	{
		for (auto i : mComponentStores)
			i->entityDestroyed(entity);
	}

private:
	std::unordered_map<const char*, size_t> mComponentTypes;
	std::array<std::shared_ptr<IComponentStore>, MAX_COMPONENTS> mComponentStores;
	ComponentID mAvailableComponentID = 0;

	// Stub for casting IComponentStore* to ComponentStore<T>*
	template<typename T>
	std::shared_ptr<ComponentStore<T>> getComponentStore()
	{
		const char* typeName = typeid(T).name();
		assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use");
		return std::static_pointer_cast<ComponentStore<T>>(mComponentStores[mComponentTypes[typeName]]);
	}
};
