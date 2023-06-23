#include "gameEngine.hpp"

#include "shader.hpp"
#include "glfwCallbacks.hpp"
#include "mesh.hpp"
#include "saveFile.hpp"
#include "factory.hpp"
#include "userInput.hpp"
#include "collisionDetection.hpp"

#include <iostream>

GameEngine::GameEngine() : world(IdGenerator::getObjectId(), nullptr)
{
    // std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    projectRootPath = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
}
GameEngine::~GameEngine()
{
    gameEngineTerminate();
}

GameEngine &GameEngine::getInstance()
{
    static GameEngine gameEngine;
    return gameEngine;
}

bool GameEngine::loadLevel(const std::string &path)
{
    return SaveFile::load(path, world, gameObjects, activeCamera);
}
bool GameEngine::saveLevel(const std::string &path)
{
    return SaveFile::save(path, world, activeCamera);
}

void GameEngine::setCursorLock(bool locked)
{
    if (locked)
    {
        m_cursorLocked = true;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        m_cursorLocked = false;
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
bool GameEngine::cursorLocked()
{
    return m_cursorLocked;
}

void GameEngine::setFullscreen(bool fullscreen)
{
    if (fullscreen)
    {
        glfwGetWindowPos(window, &windowPosX, &windowPosY);
        glfwGetWindowSize(window, &windowSizeX, &windowSizeY);

        GLFWmonitor *monitor = glfwGetPrimaryMonitor();
        const GLFWvidmode *mode = glfwGetVideoMode(monitor);

        glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
    }
    else
    {
        glfwSetWindowMonitor(window, NULL, windowPosX, windowPosY, windowSizeX, windowSizeY, 0);
    }
    return;
}
bool GameEngine::fullScreen()
{
    return glfwGetWindowMonitor(window) != NULL;
}

int GameEngine::gameEngineInit()
{
    if (isInitialized)
    {
        return 1;
    }

    if (!glfwInit())
    {
        std::cerr << "Init Failed!" << std::endl;
        return -1;
    }
    glfwSetErrorCallback(error_callback);

    glfwWindowHint(GLFW_SAMPLES, 4);               // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(640, 480, "Game Test", NULL, NULL);
    if (!window)
    {
        std::cerr << "Window Creation Failed!" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1); // V-Sync

    glfwSetInputMode(window, GLFW_LOCK_KEY_MODS, GLFW_TRUE);

    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    // glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetWindowFocusCallback(window, window_focus_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    glGenVertexArrays(1, &vertexArrayId);
    glBindVertexArray(vertexArrayId);

    // std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path projectFolder = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path().parent_path().parent_path();
    std::filesystem::path shaderFolder = projectFolder / "GameEngine/src/rendering/shaders";
    std::string vertexShaderPath = shaderFolder.string() + "/TextureVertexShader.vertexshader";
    std::string fragmentShaderPath = shaderFolder.string() + "/TextureFragmentShader.fragmentshader";
    // std::string vertexShaderPath = shaderFolder.string() + "/SimpleVertexShader.vertexshader";
    // std::string fragmentShaderPath = shaderFolder.string() + "/SimpleFragmentShader.fragmentshader";

    programId = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    mvpMatrixId = glGetUniformLocation(programId, "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    // glClearColor(0.5f, 0.5f, 0.5f, 0.0f); // Background Color
    glClearColor(0.1f, 0.1f, 0.1f, 0.0f); // Background Color

    glUseProgram(programId);

    isInitialized = true;
    return 0;
}

void GameEngine::gameEngineTerminate()
{
    if (!isInitialized)
    {
        return;
    }

    glDeleteProgram(programId);
    glDeleteVertexArrays(1, &vertexArrayId);

    glfwDestroyWindow(window);

    glfwTerminate();

    isInitialized = false;
}

void GameEngine::runGameLoop()
{
    UserInput &input = UserInput::getInstance();

    const double fixedDeltaTime = 0.01;
    const double maxFrameTime = 0.25;

    double currentTime = glfwGetTime();
    double accumulator = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        input.step();

        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        frameTime = std::min(frameTime, maxFrameTime);
        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= fixedDeltaTime)
        {
            fixedUpdate(fixedDeltaTime);
            accumulator -= fixedDeltaTime;
        }

        const double alpha = accumulator / fixedDeltaTime;

        update(frameTime);
        render(alpha);
    }
    return;
}

GameObject &GameEngine::createGameObject()
{
    return Factory::createGameObject(&world, gameObjects);
}
Camera &GameEngine::createCamera()
{
    Camera &camera = Factory::createCamera(&world, gameObjects);

    if (activeCamera == nullptr)
    {
        activeCamera = &camera;
    }

    return camera;
}
void GameEngine::addToDestroyQueue(GameObject &toDestroy)
{
    // Adds Object to be destroyed to the destruction queue
    // All queued objects are deleted at the end of the next update / fixedUpdate
    destructionQueue.push(toDestroy.id);
    return;
}

void GameEngine::registerCollider(Collider &collider)
{
    colliders.insert(std::make_pair(collider.id, &collider));
    return;
}
void GameEngine::removeCollider(Collider &collider)
{
    colliders.erase(collider.id);
    return;
}
std::vector<Collider::CollisionInfo> GameEngine::getCollisions(GameObject &gameObject) const
{
    std::vector<Collider::CollisionInfo> result;
    for (auto &component : gameObject.getComponents())
    {
        if (component->type() != "Collider")
        {
            continue;
        }
        Collider &collider = dynamic_cast<Collider &>(*component);
        auto tmp = getCollisions(collider);
        result.insert(result.end(), std::make_move_iterator(tmp.begin()), std::make_move_iterator(tmp.end()));
    }
    return result;
}
std::vector<Collider::CollisionInfo> GameEngine::getCollisions(const Collider &collider) const
{
    std::vector<Collider::CollisionInfo> result;
    if (collisions.contains(collider.id))
    {
        result = collisions.at(collider.id);
    }
    return result;
}

std::filesystem::path GameEngine::defaultAssetFolder() const
{
    return projectRootPath / "GameEngine/src/rendering/defaultAssets";
}
std::filesystem::path GameEngine::projectAssetFolder() const
{
    return projectRootPath / "testAssets";
}

void GameEngine::update(double deltaTime)
{
    for (auto &gameObject : gameObjects)
    {
        gameObject.second->update(deltaTime);
    }
    destroyQueuedObjects();
    return;
}
void GameEngine::fixedUpdate(double deltaTime)
{
    processCollisions();
    for (auto &gameObject : gameObjects)
    {
        gameObject.second->saveState();
    }
    for (auto &gameObject : gameObjects)
    {
        gameObject.second->fixedUpdate(deltaTime);
    }
    destroyQueuedObjects();
    return;
}
void GameEngine::render(double interpolation)
{
    float ratio;
    int width, height;

    glfwGetFramebufferSize(window, &width, &height);
    ratio = width / (float)height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Setting a fixed resolution causes stretching if window shape changes
    // Updating causes lags? and crashes when switching to desktop (if ratio weird)
    activeCamera->setRatio(ratio);

    // TODO: Improve performance
    if (activeCamera != nullptr)
    {
        for (auto &gameObject : gameObjects)
        {
            for (auto &component : gameObject.second->getComponents())
            {
                if (component->type() == "Mesh")
                {
                    Mesh &toDraw = dynamic_cast<Mesh &>(*component);
                    toDraw.render(*activeCamera, interpolation);
                }
            }
        }
    }
    // glFinish();
    glfwSwapBuffers(window);
    // glFinish();
}

void GameEngine::processCollisions()
{
    collisions.clear();
    collisions.reserve(colliders.size());

    // Could be optimized:
    // Collisions between pairs are calculated twice
    for (auto &entry : colliders)
    {
        Collider &collider = *entry.second;
        std::vector<Collider::CollisionInfo> tmpCollisions;

        for (auto &entryOther : colliders)
        {
            Collider &colliderOther = *entryOther.second;

            if (collider.parent()->id == colliderOther.parent()->id)
            {
                continue;
            }

            Collider::CollisionInfo info(&colliderOther);
            // All colliders are assumed to be spheres
            if (CollisionDetection::collisionSpheres(collider, colliderOther, info))
            {
                tmpCollisions.push_back(std::move(info));
            }
        }
        collisions.insert(std::make_pair(collider.id, std::move(tmpCollisions)));
    }
    return;
}

void GameEngine::destroyQueuedObjects()
{
    while (!destructionQueue.empty())
    {
        gameObjects.erase(destructionQueue.front());
        destructionQueue.pop();
    }
    return;
}
