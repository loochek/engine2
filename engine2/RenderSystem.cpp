#include "RenderSystem.h"
#include <iostream>

int RenderSystem::init(EventDispatcher* eventDispatcher)
{
    mEventDispatcher = eventDispatcher;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(800, 600, "engine2", NULL, NULL);
    if (!mWindow)
    {
        std::cout << "[RenderSystem] Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[RenderSystem] Failed to initialize GLAD" << std::endl;
        return -1;
    }
    return 0;
}

void RenderSystem::update(GLfloat elapsedTime)
{
    if (glfwWindowShouldClose(mWindow))
        mEventDispatcher->emit(new ApplicationTerminateEvent());
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    std::cout << "FPS: " << 1.f / elapsedTime << std::endl;
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void RenderSystem::shutdown()
{
    glfwTerminate();
}