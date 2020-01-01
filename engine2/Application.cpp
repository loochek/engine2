#include "Application.h"
#include <iostream>
#include <chrono>
#include <vector>

int Application::init()
{
    ObjectController& objectController = ObjectController::getInstance();

    objectController.registerComponent<MeshComponent>();
    objectController.registerComponent<RenderableComponent>();
    
    mRenderSystem = objectController.registerSystem<RenderSystem>();
    objectController.setSystemRequirement<RenderSystem, RenderableComponent>(true);
    if (mRenderSystem->init())
        return -1;

    EventDispatcher::getInstance().subscribe(this, &Application::onApplicationTerminateEvent);

    Entity triangle = objectController.createEntity();
    std::vector<glm::vec3> vertices = {glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f,  0.5f, 0.0f)};
    std::vector<glm::vec2> texCoords = { glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 0.0f), glm::vec2(0.5f, 1.0f) };
    objectController.addComponent(triangle, RenderableComponent());
    objectController.addComponent(triangle, MeshComponent());
    objectController.getComponent<MeshComponent>(triangle).cMesh.loadPositions(vertices);
    objectController.getComponent<MeshComponent>(triangle).cMesh.loadTexCoords(texCoords);
    objectController.getComponent<MeshComponent>(triangle).cMesh.bake();
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
    using clock = std::chrono::high_resolution_clock;
    auto lastTime = clock::now();
    while (!mShouldClose)
    {
        auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - lastTime);
        lastTime = clock::now();
        mRenderSystem->update(elapsedTime.count() / 1000000.0f);
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
