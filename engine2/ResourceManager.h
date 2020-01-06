#pragma once

#include <unordered_map>
#include "Shader.h"
#include "Model.h"
#include "Texture.h"
#include "Material.h"

class ResourceManager
{
public:
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	static ResourceManager& getInstance();

	std::shared_ptr<Shader> getShader(const std::string& name);
	std::shared_ptr<Texture> getTexture(const std::string& name);
	std::shared_ptr<Material> getMaterial(const std::string& name);
	std::shared_ptr<Model> getModel(const std::string& name);

private:
	ResourceManager() {}
	~ResourceManager() {}
	std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
	std::unordered_map<std::string, std::shared_ptr<Material>> mMaterials;
	std::unordered_map<std::string, std::shared_ptr<Texture>> mTextures;
	std::unordered_map<std::string, std::shared_ptr<Model>> mModels;
};