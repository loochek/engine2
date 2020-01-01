#pragma once

#include <memory>
#include <unordered_map>
#include "Entity.h"
#include "System.h"

class SystemManager
{
public:
	template<typename T>
	std::shared_ptr<T> registerSystem()
	{
		const char* typeName = typeid(T).name();
		assert(mSystems.find(typeName) == mSystems.end() && "Registering system more than once");

		auto system = std::make_shared<T>();
		mSystems[typeName] = system;
		return system;
	}

	template<typename T>
	void setSignature(Signature signature)
	{
		const char* typeName = typeid(T).name();
		assert(mSystems.find(typeName) != mSystems.end() && "System used before registered");

		mSignatures[typeName] = signature;
	}

	template<typename T>
	Signature getSignature()
	{
		return mSignatures[typeid(T).name()];
	}

	void entityDestroyed(Entity entity)
	{
		for (auto i : mSystems)
			i.second->mEntities.erase(entity);
	}

	void entitySignatureChanged(Entity entity, Signature signature)
	{
		for (auto const& pair : mSystems)
		{
			auto const& type = pair.first;
			auto const& system = pair.second;
			auto const& systemSignature = mSignatures[type];

			// Entity signature matches system signature - insert into set
			if ((signature & systemSignature) == systemSignature)
			{
				system->mEntities.insert(entity);
			}
			// Entity signature does not match system signature - erase from set
			else
			{
				system->mEntities.erase(entity);
			}
		}
	}

private:
	std::unordered_map<const char*, Signature> mSignatures;
	std::unordered_map<const char*, std::shared_ptr<System>> mSystems;
};