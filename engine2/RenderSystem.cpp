#include "RenderSystem.h"
#include <iostream>
#include "ObjectController.h"
#include "Components.h"
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.h"

int RenderSystem::init()
{
    glEnable(GL_DEPTH_TEST);
    texture = new Texture("textures/emo.jpg");
    return 0;
}

void RenderSystem::update(GLfloat elapsedTime)
{

    //std::cout << "FPS: " << 1.f / elapsedTime << std::endl;
    ObjectController::getInstance().getComponent<TransformComponent>(0).rotationAngle += glm::radians(100.f * elapsedTime);

    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    texture->bind(0);

    auto& objectController = ObjectController::getInstance();

    for (auto i : mEntities)
    {
        glm::mat4 trans(1.0f);
        if (objectController.hasComponent<TransformComponent>(i))
        {
            auto& transform = ObjectController::getInstance().getComponent<TransformComponent>(i);
            trans = glm::scale(trans, transform.scale);
            trans = glm::rotate(trans, transform.rotationAngle, transform.rotationAxis);
            trans = glm::translate(trans, transform.translation);
        }
        auto shader = ResourceManager::getInstance().getShader("shader");
        shader->bind();
        shader->setMat4f("transform", trans);
        shader->setMat4f("view", glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)));
        shader->setMat4f("projection", glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f));
        Shader::unbind();
        ObjectController::getInstance().getComponent<MeshComponent>(i).cMesh->draw(*shader);
    }

    Texture::unbind(0);
}

void RenderSystem::shutdown()
{
}