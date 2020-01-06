#pragma once

#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture();
	Texture(const std::string& path);
	~Texture();

	void bind(GLuint textureUnit);
	static void unbind(GLuint textureUnit);

private:
	GLuint mTexID;
};