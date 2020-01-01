#include "RenderSystem.h"
#include <iostream>
#include "ObjectController.h"
#include "Components.h"

int RenderSystem::init()
{
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

    shader = new Shader("shaders/shader.vert", "shaders/shader.frag");
    texture = new Texture("textures/wall.jpg");
    return 0;
}

void RenderSystem::update(GLfloat elapsedTime)
{
    if (glfwWindowShouldClose(mWindow))
        EventDispatcher::getInstance().emit(new ApplicationTerminateEvent());

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    texture->bind(0);
    for (auto i : mEntities)
        ObjectController::getInstance().getComponent<MeshComponent>(i).cMesh.draw(*shader);
    Texture::unbind(0);
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void RenderSystem::shutdown()
{
    glfwTerminate();
}