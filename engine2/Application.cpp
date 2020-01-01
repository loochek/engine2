#include "Application.h"
#include <iostream>

int Application::init()
{
    mRenderSystem = mObjectController.registerSystem<RenderSystem>();
    if (mRenderSystem->init(&mEventDispatcher))
        return -1;
    mEventDispatcher.subscribe(this, &Application::onApplicationTerminateEvent);
    return 0;
}

int Application::run()
{
    if (init())
    {
        std::cout << "[FATAL] Initialization failed, exiting..." << std::endl;
        terminate();
        return -1;
    }
    GLfloat lastTime = glfwGetTime();
    while (!mShouldClose)
    {
        GLfloat elapsedTime = glfwGetTime() - lastTime;
        lastTime = glfwGetTime();

        mRenderSystem->update(elapsedTime);
    }
    terminate();
	return 0;
}

void Application::terminate()
{
    mRenderSystem->shutdown();
}

void Application::onApplicationTerminateEvent(ApplicationTerminateEvent* event)
{
    mShouldClose = true;
}
