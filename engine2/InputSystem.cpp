#include "InputSystem.h"

std::array<bool, 5> InputSystem::mKeyboardState;
std::array<bool, 5> InputSystem::mKeyboardStateOld;
GLfloat InputSystem::mMouseX;
GLfloat InputSystem::mMouseY;
GLfloat InputSystem::mMouseXOld;
GLfloat InputSystem::mMouseYOld;

// this is weird
void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	int keys[] = { GLFW_KEY_ESCAPE, GLFW_KEY_W, GLFW_KEY_A, GLFW_KEY_S, GLFW_KEY_D };
	for (int i = 0; i < 5; i++)
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
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	return 0;
}

void InputSystem::update(GLfloat elapsedTime)
{
	if (mKeyboardState != mKeyboardStateOld)
	{
		EventDispatcher::getInstance().emit(KeyboardStateBroadcastEvent(mKeyboardState));
		mKeyboardStateOld = mKeyboardState;
	}
	GLfloat xOffset = mMouseX - mMouseXOld;
	GLfloat yOffset = mMouseYOld - mMouseY;
	mMouseXOld = mMouseX;
	mMouseYOld = mMouseY;
	EventDispatcher::getInstance().emit(MouseMovedEvent(xOffset, yOffset));
}

void InputSystem::shutdown()
{
}