#pragma once

#include <memory>
#include <array>
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

	friend void glfwKeyCallback(GLFWwindow*, int, int, int, int);
	friend void glfwMouseCallback(GLFWwindow*, double, double);

private:
	GLFWwindow* mWindow;
	// this is weird
	static std::array<bool, 5> mKeyboardState;
	static std::array<bool, 5> mKeyboardStateOld;
	static GLfloat mMouseX;
	static GLfloat mMouseXOld;
	static GLfloat mMouseY;
	static GLfloat mMouseYOld;
};