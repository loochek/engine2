#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include "Shader.h"
#include "Material.h"
#include "Renderable.h"

class Mesh : public Renderable
{
public:
	Mesh() {};
	Mesh(const Mesh&) = delete;
	//Mesh(Mesh&& another);
	Mesh& operator=(const Mesh&) = delete;

	Mesh(Mesh&&) = default;
	Mesh& operator=(Mesh&&) = default;

	void loadPositions(const std::vector<glm::vec3>& positions);
	void loadTexCoords(const std::vector<glm::vec2>& texCoords);
	void loadNormals(const std::vector<glm::vec3>& normals);
	void loadIndices(const std::vector<GLuint>& Indices);
	void setMaterial(const std::shared_ptr<Material>& material);
	void bake();
	void draw();

protected:
	GLuint mVBO{}, mIBO{}, mVAO{};
	std::vector<glm::vec3> mPositions;
	std::vector<glm::vec2> mTexCoords;
	std::vector<glm::vec3> mNormals;
	std::vector<GLuint> mIndices;
	std::shared_ptr<Material> mMaterial;
};