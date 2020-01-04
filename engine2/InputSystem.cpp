#include "InputSystem.h"
#include <iostream>

std::array<bool, 6> InputSystem::mKeyboardState;
std::array<bool, 6> InputSystem::mKeyboardStateOld;
GLfloat InputSystem::mMouseX;
GLfloat InputSystem::mMouseY;
GLfloat InputSystem::mMouseXOld;
GLfloat InputSystem::mMouseYOld;

// this is weird
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int keys[] = { GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D, GLFW_KEY_C };
	for (int i = 0; i < 6; i++)
	{
		if (key == keys[i])
		{
			if (action == GLFW_PRESS)
				InputSystem::mKeyboardState[i] = true;
			else if (action == GLFW_RELEASE)
				InputSystem::mKeyboardState[i] = false;
		}
	}
}

// this is weird
void glfwMouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	InputSystem::mMouseX = xpos;
	InputSystem::mMouseY = ypos;
}

int InputSystem::init(GLFWwindow* window)
{
	mWindow = window;
	glfwSetKeyCallback(mWindow, glfwKeyCallback);
	glfwSetCursorPosCallback(mWindow, glfwMouseCallback);
	return 0;
}

void InputSystem::update(GLfloat elapsedTime)
{
	if (mKeyboardState != mKeyboardStateOld)
	{
		if (!mDetatched)
			EventDispatcher::getInstance().emit(KeyboardStateBroadcastEvent(mKeyboardState));
		mKeyboardStateOld = mKeyboardState;
	}
	if (mKeyboardState[5])
	{
		mDetatched = true;
		glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		mDetatched = false;
		glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
	GLfloat xOffset = mMouseX - mMouseXOld;
	GLfloat yOffset = mMouseYOld - mMouseY;
	mMouseXOld = mMouseX;
	mMouseYOld = mMouseY;
	if (!mDetatched)
		EventDispatcher::getInstance().emit(MouseMovedEvent(xOffset, yOffset));	
}

void InputSystem::shutdown()
{
}