#include "gameEngine.hpp"

#include "shader.hpp"
#include "glfwCallbacks.hpp"
#include "mesh.hpp"

#include <iostream>

GameEngine::GameEngine() : world(IdGenerator::getObjectId(), nullptr)
{
    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    defaultAssetPath = projectFolder / "GameEngine/src/rendering/defaultAssets";
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

    /*
    glGenBuffers(1, &vertexbuffer);
    glGenBuffers(1, &colorbuffer);
    */

    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
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

    /*
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
        0,        // attribute 0. No particular reason for 0, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );

    // 2nd attribute buffer : colors
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glVertexAttribPointer(
        1,        // attribute. No particular reason for 1, but must match the layout in the shader.
        3,        // size
        GL_FLOAT, // type
        GL_FALSE, // normalized?
        0,        // stride
        (void *)0 // array buffer offset
    );
    */

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

    /*
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    */
    glDeleteProgram(programId);
    /*
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    */
    glDeleteVertexArrays(1, &vertexArrayId);

    glfwDestroyWindow(window);

    glfwTerminate();

    isInitialized = false;
}

GameObject &GameEngine::createGameObject()
{
    uint64_t id = IdGenerator::getObjectId();
    std::unique_ptr<GameObject> objectPrt = std::make_unique<GameObject>(id, &world);
    GameObject *rawPtr = objectPrt.get();

    gameObjects.insert(std::make_pair(id, std::move(objectPrt)));

    return *rawPtr;
}
Camera &GameEngine::createCamera()
{
    uint64_t id = IdGenerator::getObjectId();
    // Camera *rawPtr = new Camera(id, &world, vertexbuffer, colorbuffer, mvpMatrixId);
    Camera *rawPtr = new Camera(id, &world);
    std::unique_ptr<GameObject> objectPtr(rawPtr);

    gameObjects.insert(std::make_pair(id, std::move(objectPtr)));

    if (activeCamera == nullptr)
    {
        activeCamera = rawPtr;
    }

    return *rawPtr;
}
void GameEngine::destroyGameObject(GameObject &toDestroy)
{
    // Adds Object to be destroyed to the destruction queue
    // All queued objects are deleted at the end of the next update / fixedUpdate
    destructionQueue.push(toDestroy.id);
    return;
}

const std::filesystem::path &GameEngine::defaultAssetFolder() const
{
    return defaultAssetPath;
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
    for (auto &gameObject : gameObjects)
    {
        gameObject.second->transform.savePreviousState();
    }
    for (auto &gameObject : gameObjects)
    {
        gameObject.second->fixedUpdate(deltaTime);
    }
    destroyQueuedObjects();
    return;
}
void GameEngine::render()
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
                    toDraw.render(*activeCamera);
                }
            }
        }
    }
    // glFinish();
    glfwSwapBuffers(window);
    // glFinish();
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
