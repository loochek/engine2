#include "Model.h"
#include "ResourceManager.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include <glm/gtc/type_ptr.hpp>

Model::Model(Token, const std::string& path)
{
	std::ifstream modelFile(path, std::ios::binary);
	E2mdlHeader header;
	modelFile.read((char*)&header, sizeof(E2mdlHeader));
	char* sign = header.signature;
	if (strcmp(sign, "E2MDL"))
	{
		std::cout << "ERROR: file is not a valid model file" << std::endl;
		return;
	}
	size_t offset = sizeof(E2mdlHeader);
	mMeshes.resize(header.meshCount);
	for (size_t i = 0; i < header.meshCount; i++)
	{
		E2mdlMeshEntry meshEntry;
		modelFile.read((char*)&meshEntry, sizeof(E2mdlMeshEntry));
		std::vector<glm::vec3> vertices(meshEntry.verticesCount);
		for (size_t j = 0; j < meshEntry.verticesCount; j++)
		{
			glm::vec3 vertice;
			modelFile.read((char*)glm::value_ptr(vertice), sizeof(glm::vec3));
			vertices[j] = vertice;
		}
		mMeshes[i].loadPositions(vertices);

		std::vector<glm::vec3> normals(meshEntry.verticesCount);
		for (size_t j = 0; j < meshEntry.verticesCount; j++)
		{
			glm::vec3 normal;
			modelFile.read((char*)glm::value_ptr(normal), sizeof(glm::vec3));
			normals[j] = normal;
		}
		mMeshes[i].loadNormals(normals);

		std::vector<GLuint> indices(meshEntry.verticesCount);
		for (size_t j = 0; j < meshEntry.verticesCount; j++)
		{
			GLuint index;
			modelFile.read((char*)&index, sizeof(GLuint));
			indices[j] = index;
		}
		mMeshes[i].loadIndices(indices);	

		if (meshEntry.flags & 1)
		{
			std::vector<glm::vec2> texCoords(meshEntry.verticesCount);
			for (size_t j = 0; j < meshEntry.verticesCount; j++)
			{
				glm::vec2 texCoord;
				modelFile.read((char*)glm::value_ptr(texCoord), sizeof(glm::vec2));
				texCoords[j] = texCoord;
			}
			mMeshes[i].loadTexCoords(texCoords);
		}
		mMeshes[i].setMaterial(ResourceManager::getInstance().getMaterial(meshEntry.material));
		mMeshes[i].bake();
	}
	modelFile.close();
}

void Model::draw()
{
	for (auto& i : mMeshes)
		i.draw();
}