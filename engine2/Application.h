#pragma once

#include "EventDispatcher.h"
#include "ObjectController.h"
#include "RenderSystem.h"
#include "Components.h"

class Application
{
public:
	int init();
	int run();
	void terminate();

private:
	std::shared_ptr<RenderSystem> mRenderSystem;
	bool mShouldClose = false;
	void onApplicationTerminateEvent(ApplicationTerminateEvent* event);
};