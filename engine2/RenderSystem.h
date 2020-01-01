#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "System.h"
#include "EventDispatcher.h"

class RenderSystem : public System
{
public:
	int init(EventDispatcher* eventDispatcher);
	void update(GLfloat elapsedTime);
	void shutdown();

private:
	GLFWwindow* mWindow;
	EventDispatcher* mEventDispatcher;
};