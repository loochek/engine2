#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "System.h"
#include "EventDispatcher.h"
#include "Shader.h"

class RenderSystem : public System
{
public:
	int init();
	void update(GLfloat elapsedTime);
	void shutdown();

private:
	GLFWwindow* mWindow;
	Shader *shader;
};