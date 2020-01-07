#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "System.h"
#include "EventDispatcher.h"
#include "Shader.h"
#include "Texture.h"

class RenderSystem : public System
{
public:
	int init();
	void update(GLfloat elapsedTime);
	void shutdown();
	void setCamera(Entity camera);

private:
	Entity mCurrentCamera = MAX_ENTITIES;
	int mWindowWidth = {};
	int mWindowHeight = {};
	void onFramebufferResizeEvent(const FramebufferResizeEvent& event);
};