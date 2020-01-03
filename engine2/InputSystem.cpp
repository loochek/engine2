#include "InputSystem.h"

int InputSystem::init(GLFWwindow* window)
{
	mWindow = window;
	return 0;
}

void InputSystem::update(GLfloat elapsedTime)
{
	auto& eventDispatcher = EventDispatcher::getInstance();
	if (mKeyStates[0] && glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
	{
		eventDispatcher.emit(KeyReleasedEvent(GLFW_KEY_ESCAPE));
		mKeyStates[0] = false;
	}
	else if (!mKeyStates[0] && glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		eventDispatcher.emit(KeyPressedEvent(GLFW_KEY_ESCAPE));
		mKeyStates[0] = true;
	}
	if (mKeyStates[1] && glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_RELEASE)
	{
		eventDispatcher.emit(KeyReleasedEvent(GLFW_KEY_W));
		mKeyStates[1] = false;
	}
	else if (!mKeyStates[1] && glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
	{
		eventDispatcher.emit(KeyPressedEvent(GLFW_KEY_W));
		mKeyStates[1] = true;
	}
	if (mKeyStates[2] && glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_RELEASE)
	{
		eventDispatcher.emit(KeyReleasedEvent(GLFW_KEY_A));
		mKeyStates[2] = false;
	}
	else if (!mKeyStates[2] && glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
	{
		eventDispatcher.emit(KeyPressedEvent(GLFW_KEY_A));
		mKeyStates[2] = true;
	}
	if (mKeyStates[3] && glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_RELEASE)
	{
		eventDispatcher.emit(KeyReleasedEvent(GLFW_KEY_S));
		mKeyStates[3] = false;
	}
	else if (!mKeyStates[3] && glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
	{
		eventDispatcher.emit(KeyPressedEvent(GLFW_KEY_S));
		mKeyStates[3] = true;
	}
	if (mKeyStates[4] && glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_RELEASE)
	{
		eventDispatcher.emit(KeyReleasedEvent(GLFW_KEY_D));
		mKeyStates[4] = false;
	}
	else if (!mKeyStates[4] && glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
	{
		eventDispatcher.emit(KeyPressedEvent(GLFW_KEY_D));
		mKeyStates[4] = true;
	}
}

void InputSystem::shutdown()
{
}