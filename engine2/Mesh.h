#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include "Shader.h"

class Mesh
{
public:
	// the trick to give resoures creation exclusive right to ResourceManager
	class Token
	{
	private:
		Token() {}
		friend class ResourceManager;
	};
	Mesh(Token) {};
	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

	void loadPositions(std::vector<glm::vec3>& positions);
	void loadTexCoords(std::vector<glm::vec2>& texCoords);
	void loadNormals(std::vector<glm::vec3>& normals);
	void bake();
	void draw(Shader &shader);

private:
	GLuint mVBO{}, mVAO{};
	std::vector<glm::vec3> mPositions;
	std::vector<glm::vec2> mTexCoords;
	std::vector<glm::vec3> mNormals;
};