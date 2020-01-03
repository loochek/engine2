#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Shader
{
public:
	// the trick to give resoures creation exclusive right to ResourceManager
	class Token
	{
	private:
		Token() {}
		friend class ResourceManager;
	};

	Shader() = delete;
	~Shader();
	Shader(Token, const std::string& vertexPath, const std::string& fragmentPath);
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	void bind();
	static void unbind();
	void setFloat(const GLchar* uniform, GLfloat value);
	void setInt(const GLchar* uniform, GLint value);
	void setVec3f(const GLchar* uniform, GLfloat value1, GLfloat value2, GLfloat value3);
	void setVec3f(const GLchar* uniform, glm::vec3 vec);
	void setMat4f(const GLchar* uniform, glm::mat4 mat);

private:
	GLuint program;
};