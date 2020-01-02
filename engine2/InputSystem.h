#pragma once

#include <memory>
#include <glad/glad.h>
#include "System.h"
#include "EventDispatcher.h"
#include <GLFW/glfw3.h>

class InputSystem : public System
{
public:
	int init(GLFWwindow* window);
	void update(GLfloat elapsedTime);
	void shutdown();
private:
	GLFWwindow* mWindow;
};