#pragma once

#include "EventDispatcher.h"
#include "ObjectController.h"
#include "RenderSystem.h"

class Application
{
public:
	int init();
	int run();
	void terminate();

private:
	ObjectController mObjectController;
	EventDispatcher mEventDispatcher;
	std::shared_ptr<RenderSystem> mRenderSystem;
	bool mShouldClose = false;
	void onApplicationTerminateEvent(ApplicationTerminateEvent* event);
};