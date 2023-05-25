#pragma once

#include "gameObject.hpp"
#include "idGenerator.hpp"
#include "camera.hpp"

#include <map>
#include <memory>
#include <queue>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

// This class is a singleton
class GameEngine
{
public:
    Camera *activeCamera;
    GLFWwindow *window;

    static GameEngine &getInstance();

    void setCursorLock(bool locked);
    bool cursorLocked();
    void setFullscreen(bool fullscreen);
    bool fullScreen();

    int gameEngineInit();
    void gameEngineTerminate();

    GameObject &createGameObject();
    Camera &createCamera();
    void destroyGameObject(GameObject &toDestroy);

    const std::filesystem::path &defaultAssetFolder() const;

    void update(double deltaTime);
    void fixedUpdate(double deltaTime);

    void render();

    GameEngine(GameEngine const &) = delete;
    void operator=(GameEngine const &) = delete;

    GLuint mvpMatrixId;

private:
    GLuint vertexArrayId;
    /*
    GLuint vertexbuffer;
    GLuint colorbuffer;
    */
    GLuint programId;

    bool isInitialized;
    bool m_cursorLocked = false;

    // These are only used to store the values when switching to fullscreen
    int windowPosX = 0;
    int windowPosY = 0;
    int windowSizeX = 0;
    int windowSizeY = 0;

    GameObject world;
    std::map<uint64_t, std::unique_ptr<GameObject>> gameObjects; // switch to unordered_map ?
    std::filesystem::path defaultAssetPath;

    std::queue<uint64_t> destructionQueue;

    GameEngine();
    ~GameEngine();

    void destroyQueuedObjects();
};
