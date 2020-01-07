#pragma once

#include <vector>
#include "Renderable.h"
#include "Shader.h"
#include "Mesh.h"

#pragma pack (push)
#pragma pack (1)
struct E2mdlHeader
{
	char signature[6];
	uint8_t version;
	uint32_t meshCount;
};
#pragma pack (pop)

#pragma pack (push)
#pragma pack (1)
struct E2mdlMeshEntry
{
	char signature[5];
	uint32_t verticesCount;
	uint32_t indicesCount;
	uint8_t flags; // UV present - 1st bit
	char material[128]; // used material
};
#pragma pack (pop)

/*
header

mesh entry - vertices count, indices count
mesh data
{
	vertices - sizeof(glm::vec3) * verticesCount
	normals - sizeof(glm::vec3) * verticesCount
	Indices - sizeof(GLfloat) * indicesCount
	uv coords - sizeof(glm::vec2) * verticesCount if flag set
}
mesh data {}
...
*/

class Model : public Renderable
{
public:
	// the trick to give resoures creation exclusive right to ResourceManager
	class Token
	{
	private:
		Token() {}
		friend class ResourceManager;
	};

	Model(Token, const std::string& path);
	Model(const Model&) = delete;
	Model& operator=(const Model&) = delete;

	void draw();

private:
	std::vector<Mesh> mMeshes;
};