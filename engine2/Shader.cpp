#include "Shader.h"
#include <glm/gtc/type_ptr.hpp>

Shader::~Shader()
{
	glDeleteProgram(this->program);
}

Shader::Shader(Token, const std::string& vertexPath, const std::string& fragmentPath)
{
	std::ifstream vShaderFin;
	std::ifstream fShaderFin;

	vShaderFin.open(vertexPath);
	fShaderFin.open(fragmentPath);
	std::stringstream vShaderBuffer, fShaderBuffer;
	vShaderBuffer << vShaderFin.rdbuf();
	fShaderBuffer << fShaderFin.rdbuf();
	vShaderFin.close();
	fShaderFin.close();

	std::string vertexCode = vShaderBuffer.str();
	std::string fragmentCode = fShaderBuffer.str();
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();

	GLuint vertex, fragment;
	GLint success;
	GLchar infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);

	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "[Shader] Vertex shader compilation failed:\n" << infoLog << std::endl;
	};

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);

	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "[Shader] Fragment shader compilation failed:\n" << infoLog << std::endl;
	};

	this->program = glCreateProgram();
	glAttachShader(this->program, vertex);
	glAttachShader(this->program, fragment);
	glLinkProgram(this->program);

	glGetProgramiv(this->program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(this->program, 512, NULL, infoLog);
		std::cout << "[Shader] Shader program linking failed:\n" << infoLog << std::endl;
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::bind()
{
	glUseProgram(this->program);
}

void Shader::unbind()
{
	glUseProgram(0);
}

void Shader::setFloat(const GLchar* uniform, GLfloat value)
{
	glUniform1f(glGetUniformLocation(this->program, uniform), value);
}

void Shader::setInt(const GLchar* uniform, GLint value)
{
	glUniform1i(glGetUniformLocation(this->program, uniform), value);
}

void Shader::setVec3f(const GLchar* uniform, GLfloat value1, GLfloat value2, GLfloat value3)
{
	glUniform3f(glGetUniformLocation(this->program, uniform), value1, value2, value3);
}

void Shader::setVec3f(const GLchar* uniform, glm::vec3 vec)
{
	glUniform3fv(glGetUniformLocation(this->program, uniform), 1, glm::value_ptr(vec));
}

void Shader::setMat4f(const GLchar* uniform, glm::mat4 mat)
{
	glUniformMatrix4fv(glGetUniformLocation(this->program, uniform), 1, GL_FALSE, glm::value_ptr(mat));
}