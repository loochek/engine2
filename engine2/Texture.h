#pragma once

#include <glad/glad.h>

class Texture
{
public:
	Texture();
	Texture(const char* loadPath);

	void bind(GLuint textureUnit);
	static void unbind(GLuint textureUnit);
private:
	GLuint mTexID;
};