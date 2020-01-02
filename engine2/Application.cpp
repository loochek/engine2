#include "Application.h"
#include "ResourceManager.h"
#include <iostream>
#include <chrono>
#include <vector>
#include "windows.h"

int Application::init()
{
    ObjectController& objectController = ObjectController::getInstance();

    objectController.registerComponent<MeshComponent>();
    objectController.registerComponent<RenderableComponent>();
    objectController.registerComponent<TransformComponent>();

    mRenderSystem = objectController.registerSystem<RenderSystem>();
    objectController.setSystemRequirement<RenderSystem, RenderableComponent>(true);
    if (mRenderSystem->init())
        return -1;

    EventDispatcher::getInstance().subscribe(this, &Application::onApplicationTerminateEvent);
    std::vector<glm::vec3> vertices = {
    {-0.5f, -0.5f, -0.5f},
    {0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
   {  0.5f,  0.5f, -0.5f},
   { -0.5f,  0.5f, -0.5f},
   { -0.5f, -0.5f, -0.5f},

   { -0.5f, -0.5f,  0.5f},
   {  0.5f, -0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
   {  0.5f,  0.5f,  0.5f},
   { -0.5f,  0.5f,  0.5f},
   { -0.5f, -0.5f,  0.5f},

    {-0.5f,  0.5f,  0.5f},
   { -0.5f,  0.5f, -0.5f},
   { -0.5f, -0.5f, -0.5f},
   { -0.5f, -0.5f, -0.5f},
   { -0.5f, -0.5f,  0.5f},
   { -0.5f,  0.5f,  0.5f},

    { 0.5f,  0.5f,  0.5f},
    { 0.5f,  0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},

   { -0.5f, -0.5f, -0.5f},
   {  0.5f, -0.5f, -0.5f},
   {  0.5f, -0.5f,  0.5f},
   {  0.5f, -0.5f,  0.5f},
   { -0.5f, -0.5f,  0.5f},
   { -0.5f, -0.5f, -0.5f},

   { -0.5f,  0.5f, -0.5f},
   {  0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f,  0.5f},
   {  0.5f,  0.5f,  0.5f},
   { -0.5f,  0.5f,  0.5f},
   { -0.5f,  0.5f, -0.5f}
    };
    std::vector<glm::vec2> texCoords = {
    {0.0f, 0.0f},
     {1.0f, 0.0f},
     { 1.0f, 1.0f},
     { 1.0f, 1.0f},
    {0.0f, 1.0f},
    { 0.0f, 0.0f},

    { 0.0f, 0.0f},
    { 1.0f, 0.0f},
     { 1.0f, 1.0f},
    {  1.0f, 1.0f},
   {  0.0f, 1.0f},
    { 0.0f, 0.0f},

    { 1.0f, 0.0f},
 {  1.0f, 1.0f},
    {  0.0f, 1.0f},
    {  0.0f, 1.0f},
    { 0.0f, 0.0f},
  {  1.0f, 0.0f},

    {  1.0f, 0.0f},
  {  1.0f, 1.0f},
    {  0.0f, 1.0f},
  { 0.0f, 1.0f},
     {  0.0f, 0.0f},
    { 1.0f, 0.0f},

    {  0.0f, 1.0f},
     { 1.0f, 1.0f},
    { 1.0f, 0.0f},
    { 1.0f, 0.0f},
   { 0.0f, 0.0f},
   {  0.0f, 1.0f},

   {  0.0f, 1.0f},
   { 1.0f, 1.0f},
    { 1.0f, 0.0f},
   {  1.0f, 0.0f},
   {  0.0f, 0.0f},
    {  0.0f, 1.0f}
    };
    auto mesh = ResourceManager::getInstance().getMesh("texturedCube");
    mesh->loadPositions(vertices);
    mesh->loadTexCoords(texCoords);
    mesh->bake();
    glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    for (int i = 0; i < 10; i++)
    {
        Entity ent = objectController.createEntity();
        objectController.addComponent(ent, RenderableComponent());
        objectController.addComponent(ent, MeshComponent());
        objectController.addComponent(ent, TransformComponent());
        objectController.getComponent<MeshComponent>(ent).cMesh = mesh;
        objectController.getComponent<TransformComponent>(ent).translation = cubePositions[i];
        objectController.getComponent<TransformComponent>(ent).rotationAxis = glm::vec3(1.0f, 1.0f, 1.0f);
    }
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
        mRenderSystem->update(elapsedTime.count() / 1e9);
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
