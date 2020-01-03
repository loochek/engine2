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

        glm::mat4 view(1.0f);
        // setup camera
        if (mCurrentCamera != MAX_ENTITIES)
        {
            CameraComponent& camera = objectController.getComponent<CameraComponent>(mCurrentCamera);
            glm::vec3 cameraPos(0.0f);
            if (objectController.hasComponent<TransformComponent>(mCurrentCamera))
                cameraPos = objectController.getComponent<TransformComponent>(mCurrentCamera).translation;
            glm::vec3 cameraFront;
            cameraFront.x = cos(glm::radians(camera.pitch)) * cos(glm::radians(camera.yaw));
            cameraFront.y = sin(glm::radians(camera.pitch));
            cameraFront.z = cos(glm::radians(camera.pitch)) * sin(glm::radians(camera.yaw));
            cameraFront = glm::normalize(cameraFront);
            view = glm::lookAt(cameraPos, cameraPos + cameraFront, glm::vec3(0.0f, 1.0f, 0.0f));
        }
        auto shader = ResourceManager::getInstance().getShader("shader");
        shader->bind();
        shader->setMat4f("transform", trans);
        shader->setMat4f("view", view);
        shader->setMat4f("projection", glm::perspective(45.0f, 800.f / 600.f, 0.1f, 100.0f));
        Shader::unbind();
        ObjectController::getInstance().getComponent<MeshComponent>(i).cMesh->draw(*shader);
    }

    Texture::unbind(0);
}

void RenderSystem::shutdown()
{
}

void RenderSystem::setCamera(Entity camera)
{
    if (ObjectController::getInstance().hasComponent<CameraComponent>(camera))
        mCurrentCamera = camera;
    else
        std::cout << "[RenderSystem] Entity " << camera << " is not camera!" << std::endl;
}
