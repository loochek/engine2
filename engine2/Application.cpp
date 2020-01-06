#include "Application.h"
#include "ResourceManager.h"
#include <iostream>
#include <chrono>
#include <vector>

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    EventDispatcher::getInstance().emit(FramebufferResizeEvent(width, height));
}

int Application::init()
{
    // create window, init OGL
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    mWindow = glfwCreateWindow(800, 600, "engine2", NULL, NULL);
    if (!mWindow)
    {
        std::cout << "[FATAL] Failed to create GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(mWindow);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "[FATAL] Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCallback);

    //subscribe to events
    EventDispatcher::getInstance().subscribe(this, &Application::onApplicationTerminateEvent);
    EventDispatcher::getInstance().subscribe(this, &Application::onKeyboardStateBroadcastEvent);

    //init ECS

    ObjectController& objectController = ObjectController::getInstance();

    objectController.registerComponent<MeshComponent>();
    objectController.registerComponent<RenderableComponent>();
    objectController.registerComponent<TransformComponent>();
    objectController.registerComponent<CameraComponent>();
    objectController.registerComponent<CameraControlComponent>();

    mRenderSystem = objectController.registerSystem<RenderSystem>();
    objectController.setSystemRequirement<RenderSystem, RenderableComponent>(true);
    if (mRenderSystem->init())
        return -1;

    mGUISystem = objectController.registerSystem<GUISystem>();
    if (mGUISystem->init(mWindow))
        return -1;

    mInputSystem = objectController.registerSystem<InputSystem>();
    if (mInputSystem->init(mWindow))
        return -1;

    mCameraControlSystem = objectController.registerSystem<CameraControlSystem>();
    objectController.setSystemRequirement<CameraControlSystem, TransformComponent>(true);
    objectController.setSystemRequirement<CameraControlSystem, CameraComponent>(true);
    objectController.setSystemRequirement<CameraControlSystem, CameraControlComponent>(true);
    if (mCameraControlSystem->init())
        return -1;

    // init world
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
    /*auto mesh = ResourceManager::getInstance().getMesh("texturedCube");
    mesh->loadPositions(vertices);
    mesh->loadTexCoords(texCoords);
    mesh->bake();
    auto diffuseMap = ResourceManager::getInstance().getTexture("emo.jpg");
    Material mat(diffuseMap);
    mesh->setMaterial(mat);*/
    Entity ent = objectController.createEntity();
    objectController.addComponent(ent, RenderableComponent());
    objectController.addComponent(ent, MeshComponent());
    objectController.getComponent<MeshComponent>(ent).cModel = ResourceManager::getInstance().getModel("nanosuit");
    objectController.addComponent(ent, TransformComponent());

    Entity camera = objectController.createEntity();
    objectController.addComponent(camera, TransformComponent());
    objectController.addComponent(camera, CameraComponent());
    objectController.addComponent(camera, CameraControlComponent());
    mRenderSystem->setCamera(camera);
    // hack
    EventDispatcher::getInstance().emit(FramebufferResizeEvent(800, 600));


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
        glfwPollEvents();
        GLfloat elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(clock::now() - lastTime).count() / 1e9;
        lastTime = clock::now();

        //all systems is able to draw gui
        mGUISystem->startFrame();
        mInputSystem->update(elapsedTime);
        mCameraControlSystem->update(elapsedTime);
        //ObjectController::getInstance().getComponent<TransformComponent>(0).rotation.x += glm::radians(100.f * elapsedTime);
        //ObjectController::getInstance().getComponent<TransformComponent>(0).rotation.y += glm::radians(100.f * elapsedTime);
        mRenderSystem->update(elapsedTime);
        mGUISystem->endFrame();

        glfwSwapBuffers(mWindow);
        if (glfwWindowShouldClose(mWindow))
            mShouldClose = true;
    }
    terminate();
	return 0;
}

void Application::terminate()
{
    mCameraControlSystem->shutdown();
    mInputSystem->shutdown();
    mGUISystem->shutdown();
    mRenderSystem->shutdown();
    glfwTerminate();
}

void Application::onApplicationTerminateEvent(const ApplicationTerminateEvent& event)
{
    mShouldClose = true;
}

void Application::onKeyboardStateBroadcastEvent(const KeyboardStateBroadcastEvent& event)
{
    if (event.keyboardState[0])
        EventDispatcher::getInstance().emit(ApplicationTerminateEvent());
}