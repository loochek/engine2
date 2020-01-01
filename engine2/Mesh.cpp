#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3> &vertices)
{
	glGenVertexArrays(1, &mVAO);
	glGenBuffers(1, &mVBO);

	mVerticesCount = static_cast<GLuint>(vertices.size());

	glBindVertexArray(mVAO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mVerticesCount, vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), 0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void Mesh::draw(Shader &shader)
{
	shader.use();
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mVerticesCount);
	glBindVertexArray(0);
	glUseProgram(0);
}