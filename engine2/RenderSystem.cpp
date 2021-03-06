#include "RenderSystem.h"
#include <iostream>
#include "ObjectController.h"
#include "Components.h"
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ResourceManager.h"
#include "Model.h"
#include "imgui.h"
#include "imgui_internal.h"

int RenderSystem::init()
{
    EventDispatcher::getInstance().subscribe(this, &RenderSystem::onFramebufferResizeEvent);
    glEnable(GL_DEPTH_TEST);
    return 0;
}

void RenderSystem::update(GLfloat elapsedTime)
{
    glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto& objectController = ObjectController::getInstance();

    glm::mat4 view(1.0f);
    glm::mat4 projection = glm::perspective(45.0f, static_cast<GLfloat>(mWindowWidth) / static_cast<GLfloat>(mWindowHeight), 0.1f, 100.0f);
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
        projection = glm::perspective(camera.fov, static_cast<GLfloat>(mWindowWidth) / static_cast<GLfloat>(mWindowHeight), camera.nearClipPlane, camera.farClipPlane);
       
        ImGui::SetNextWindowPos(ImVec2(10, 10));
        ImGui::SetNextWindowBgAlpha(0.35f);
        ImGui::Begin("Info", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
        ImGui::Text("Camera position: %f %f %f\nCamera pitch: %f\nCamera yaw: %f", cameraPos.x, cameraPos.y, cameraPos.z, camera.pitch, camera.yaw);
        ImGui::End();
    }

    ImGui::SetNextWindowPos(ImVec2(10, 70));
    ImGui::SetNextWindowBgAlpha(0.35f);
    ImGui::Begin("Example: Simple overlay", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
    ImGui::Text("FPS: %f", 1.f / elapsedTime);
    ImGui::End();

    for (auto i : mEntities)
    {
        glm::mat4 trans(1.0f);
        if (objectController.hasComponent<TransformComponent>(i))
        {
            auto& transform = ObjectController::getInstance().getComponent<TransformComponent>(i);
            trans = glm::scale(trans, transform.scale);
            trans *= glm::eulerAngleXYZ(transform.rotation.x, transform.rotation.y, transform.rotation.z);
            trans = glm::translate(trans, transform.translation);
        }

        auto shader = ResourceManager::getInstance().getShader("shader");
        shader->bind();
        shader->setMat4f("transform", trans);
        shader->setMat4f("view", view);
        shader->setMat4f("projection", projection);
        Shader::unbind();
        ObjectController::getInstance().getComponent<RenderableComponent>(i).cRenderable->draw();
    }
  
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

void RenderSystem::onFramebufferResizeEvent(const FramebufferResizeEvent& event)
{
    mWindowWidth = event.width;
    mWindowHeight = event.height;
    glViewport(0, 0, event.width, event.height);
}