#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include "Shader.h"

class Mesh
{
public:
	void loadPositions(std::vector<glm::vec3>& positions);
	void loadTexCoords(std::vector<glm::vec2>& texCoords);
	void loadNormals(std::vector<glm::vec3>& normals);
	void bake();
	void draw(Shader &shader);

private:
	GLuint mVBO, mVAO;
	std::vector<glm::vec3> mPositions;
	std::vector<glm::vec2> mTexCoords;
	std::vector<glm::vec3> mNormals;
};