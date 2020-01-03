#pragma once

#include "EventDispatcher.h"
#include "ObjectController.h"
#include "RenderSystem.h"
#include "InputSystem.h"
#include "Components.h"

class Application
{
public:
	int init();
	int run();
	void terminate();

private:
	GLFWwindow* mWindow;
	std::shared_ptr<RenderSystem> mRenderSystem;
	std::shared_ptr<InputSystem> mInputSystem;
	bool mShouldClose = false;
	void onApplicationTerminateEvent(const ApplicationTerminateEvent& event);
	void onKeyPressed(const KeyPressedEvent& event);
};