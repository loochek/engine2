#pragma once

#include <vector>
#include <glad/glad.h>
#include <glm/vec3.hpp>
#include "Shader.h"

class Mesh
{
public:
	Mesh(std::vector<glm::vec3> &vertices);

	void draw(Shader &shader);

private:
	GLuint mVBO, mVAO;
	GLuint mVerticesCount;
};