#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "System.h"

class GUISystem : public System
{
public:
	int init(GLFWwindow* window);
	void update(GLfloat elapsedTime);
	void shutdown();

private:
	GLFWwindow* mWindow;
};