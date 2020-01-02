#include "ResourceManager.h"

ResourceManager& ResourceManager::getInstance()
{
	static ResourceManager singleton;
	return singleton;
}

std::shared_ptr<Shader> ResourceManager::getShader(const std::string& name)
{
	if (!mShaders[name])
		mShaders[name] = std::make_shared<Shader>(Shader::Token(), "shaders/" + name + ".vert", "shaders/" + name + ".frag");
	return mShaders[name];
}

std::shared_ptr<Mesh> ResourceManager::getMesh(const std::string& name)
{
	if (!mMeshes[name])
		mMeshes[name] = std::make_shared<Mesh>(Mesh::Token());
	return mMeshes[name];
}