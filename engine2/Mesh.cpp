#include "Mesh.h"
#include <set>

void Mesh::loadPositions(const std::vector<glm::vec3>& positions)
{
	mPositions = positions;
}

void Mesh::loadTexCoords(const std::vector<glm::vec2>& texCoords)
{
	mTexCoords = texCoords;
}

void Mesh::loadNormals(const std::vector<glm::vec3>& normals)
{
	mNormals = normals;
}

void Mesh::loadIndices(const std::vector<GLuint>& Indices)
{
	mIndices = Indices;
}

void Mesh::setMaterial(const std::shared_ptr<Material>& material)
{
	mMaterial = material;
}

void Mesh::bake()
{
	size_t verticesCount = mPositions.size();
	if (verticesCount == 0)
		std::cout << "WARNING: Mesh doesn't have vertices!" << std::endl;
	if (mNormals.size() != verticesCount)
		std::cout << "WARNING: Normals definition is wrong!" << std::endl;
	if (mIndices.size() < 3)
		std::cout << "WARNING: Indices aren't present - nothing to draw!" << std::endl;

	size_t bufferSize = sizeof(glm::vec3) * verticesCount * 2; // vertices and normals

	// uv mapping is optional
	bool hasTexCoords = false;
	if (mTexCoords.size() > 0)
	{
		bufferSize += sizeof(glm::vec2) * verticesCount;
		hasTexCoords = true;
		if (mTexCoords.size() != verticesCount)
			std::cout << "WARNING: UV mapping wrong!" << std::endl;
	}

	// allocate buffer in vram
	glGenVertexArrays(1, &mVAO);
	glBindVertexArray(mVAO);
	glGenBuffers(1, &mVBO);
	glBindBuffer(GL_ARRAY_BUFFER, mVBO);
	glBufferData(GL_ARRAY_BUFFER, bufferSize, nullptr, GL_STATIC_DRAW);

	// put vertices
	GLuint offset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec3) * verticesCount, mPositions.data());
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offset);
	glEnableVertexAttribArray(0);
	offset += sizeof(glm::vec3) * verticesCount;

	// put normals
	glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec3) * verticesCount, mNormals.data());
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (GLvoid*)offset);
	glEnableVertexAttribArray(1);
	offset += sizeof(glm::vec3) * verticesCount;

	// put uv mapping is present
	if (hasTexCoords)
	{
		glBufferSubData(GL_ARRAY_BUFFER, offset, sizeof(glm::vec2) * verticesCount, mTexCoords.data());
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (GLvoid*)offset);
		glEnableVertexAttribArray(2);
		offset += sizeof(glm::vec2) * verticesCount;
	}

	// create IBO
	glGenBuffers(1, &mIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mIndices.size(), mIndices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::draw()
{
	mMaterial->bind();
	glBindVertexArray(mVAO);
	if (mIndices.size() > 0)
		glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, mPositions.size());
	glBindVertexArray(0);
	Material::unbind();
}