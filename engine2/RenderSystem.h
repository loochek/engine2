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
	Texture* texture;
	Entity mCurrentCamera{ MAX_ENTITIES };
	int mWindowWidth = 0.0f;
	int mWindowHeight = 1.0f;
	void onFramebufferResizeEvent(const FramebufferResizeEvent& event);
};