#include "Mesh.h"
#include <set>

void Mesh::loadPositions(std::vector<glm::vec3>& positions)
{
	mPositions = positions;
}

void Mesh::loadTexCoords(std::vector<glm::vec2>& texCoords)
{
	mTexCoords = texCoords;
}

void Mesh::loadNormals(std::vector<glm::vec3>& normals)
{
	mNormals = normals;
}

void Mesh::bake()
{
	size_t verticesCount = mPositions.size();
	if (verticesCount == 0)
		std::cout << "WARNING: Mesh doesn't have vertices!" << std::endl;

	size_t bufferSize = sizeof(glm::vec3) * verticesCount;
	bool hasTexCoords = false;
	bool hasNormals = false;


	if (mTexCoords.size() > 0)
	{
		bufferSize += sizeof(glm::vec2) * verticesCount;
		hasTexCoords = true;
		if (mTexCoords.size() != verticesCount)
			std::cout << "WARNING: Vertices count in mesh doesn't match!" << std::endl;
	}
	if (mNormals.size() > 0)
	{
		bufferSize += sizeof(glm::vec3) * verticesCount;
		hasNormals = true;
		if (mNormals.size() != verticesCount)
			std::cout << "WARNING: Vertices count in mesh doesn't match!" << std::endl;
	}

	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);


	GLuint offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec3) * verticesCount, mPositions.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offset);
	glEnableVertexAttribArray(0);
	offset += sizeof(glm::vec3) * verticesCount;

	if (hasTexCoords)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec2) * verticesCount, mTexCoords.data());
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)offset);
		glEnableVertexAttribArray(1);
		offset += sizeof(glm::vec2) * verticesCount;
	}

	if (hasNormals)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec3) * verticesCount, mTexCoords.data());
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offset);
		glEnableVertexAttribArray(2);
		offset += sizeof(glm::vec3) * verticesCount;
	}
	glBindVertexArray(0);
}

void Mesh::draw(Shader &shader)
{
	shader.bind();
	glBindVertexArray(mVAO);
	glDrawArrays(GL_TRIANGLES, 0, mPositions.size());
	glBindVertexArray(0);
	Shader::unbind();
}