#include "RenderSystem.h"
#include <iostream>
#include "ObjectController.h"
#include "Components.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.h"

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

    glEnable(GL_DEPTH_TEST);

    ResourceManager::getInstance().getShader("shader");
    texture = new Texture("textures/emo.jpg");
    return 0;
}

void RenderSystem::update(GLfloat elapsedTime)
{
    if (glfwWindowShouldClose(mWindow))
        EventDispatcher::getInstance().emit(new ApplicationTerminateEvent());

    //std::cout << "FPS: " << 1.f / elapsedTime << std::endl;
    ObjectController::getInstance().getComponent<TransformComponent>(0).rotationAngle += glm::radians(100.f * elapsedTime);

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind(0);

    for (auto i : mEntities)
    {
        glm::mat4 trans(1.0f);
        auto& transform = ObjectController::getInstance().getComponent<TransformComponent>(i);
        trans = glm::scale(trans, transform.scale);
        trans = glm::rotate(trans, transform.rotationAngle, transform.rotationAxis);
        trans = glm::translate(trans, transform.translation);
        auto shader = ResourceManager::getInstance().getShader("shader");
        shader->bind();
        shader->setMat4f("transform", trans);
        shader->setMat4f("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
        shader->setMat4f("projection", glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f));
        Shader::unbind();
        ObjectController::getInstance().getComponent<MeshComponent>(i).cMesh->draw(*shader);
    }

    Texture::unbind(0);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

void RenderSystem::shutdown()
{
    glfwTerminate();
}