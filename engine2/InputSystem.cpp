#include "InputSystem.h"

int InputSystem::init(GLFWwindow* window)
{
	mWindow = window;
	return 0;
}

void InputSystem::update(GLfloat elapsedTime)
{
	auto& eventDispatcher = EventDispatcher::getInstance();
	if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		eventDispatcher.emit(new KeyPressedEvent(GLFW_KEY_ESCAPE));
	else if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_RELEASE)
		eventDispatcher.emit(new KeyReleasedEvent(GLFW_KEY_ESCAPE));
	if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_PRESS)
		eventDispatcher.emit(new KeyPressedEvent(GLFW_KEY_W));
	else if (glfwGetKey(mWindow, GLFW_KEY_W) == GLFW_RELEASE)
		eventDispatcher.emit(new KeyReleasedEvent(GLFW_KEY_W));
	if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_PRESS)
		eventDispatcher.emit(new KeyPressedEvent(GLFW_KEY_A));
	else if (glfwGetKey(mWindow, GLFW_KEY_A) == GLFW_RELEASE)
		eventDispatcher.emit(new KeyReleasedEvent(GLFW_KEY_A));
	if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_PRESS)
		eventDispatcher.emit(new KeyPressedEvent(GLFW_KEY_S));
	else if (glfwGetKey(mWindow, GLFW_KEY_S) == GLFW_RELEASE)
		eventDispatcher.emit(new KeyReleasedEvent(GLFW_KEY_S));
	if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_PRESS)
		eventDispatcher.emit(new KeyPressedEvent(GLFW_KEY_D));
	else if (glfwGetKey(mWindow, GLFW_KEY_D) == GLFW_RELEASE)
		eventDispatcher.emit(new KeyReleasedEvent(GLFW_KEY_D));
}

void InputSystem::shutdown()
{
}