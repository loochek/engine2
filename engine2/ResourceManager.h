#pragma once

#include <unordered_map>
#include "Shader.h"
#include "Mesh.h"

class ResourceManager
{
public:
	static ResourceManager& getInstance();

	std::shared_ptr<Shader> getShader(const std::string& name);
	// temporarily
	std::shared_ptr<Mesh> getMesh(const std::string& name);

private:
	ResourceManager() {}                                     // Private constructor
	~ResourceManager() {}
	ResourceManager(const ResourceManager&);                 // Prevent copy-construction
	ResourceManager& operator=(const ResourceManager&);      // Prevent assignment

	std::unordered_map<std::string, std::shared_ptr<Shader>> mShaders;
	std::unordered_map<std::string, std::shared_ptr<Mesh>> mMeshes;
};