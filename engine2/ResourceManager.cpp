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

std::shared_ptr<Texture> ResourceManager::getTexture(const std::string& name)
{
	if (!mTextures[name])
		mTextures[name] = std::make_shared<Texture>("textures/" + name);
	return mTextures[name];
}

std::shared_ptr<Material> ResourceManager::getMaterial(const std::string& name)
{
	if (!mMaterials[name])
		mMaterials[name] = std::make_shared<Material>(Material::Token(), "materials/" + name + ".e2mtl");
	return mMaterials[name];
}

std::shared_ptr<Model> ResourceManager::getModel(const std::string& name)
{
	if (!mModels[name])
		mModels[name] = std::make_shared<Model>(Model::Token(), "models/" + name + ".e2mdl");
	return mModels[name];
}
