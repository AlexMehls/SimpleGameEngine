#pragma once

#include "gameObject.hpp"
#include "idGenerator.hpp"
#include "camera.hpp"

#include <map>
#include <memory>
#include <queue>

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

    int gameEngineInit();
    void gameEngineTerminate();

    GameObject &createGameObject();
    Camera &createCamera();
    void destroyGameObject(GameObject &toDestroy);

    void update(double deltaTime);
    void fixedUpdate(double deltaTime);

    void render();

    GameEngine(GameEngine const &) = delete;
    void operator=(GameEngine const &) = delete;

    GLuint mvpMatrixId;

private:
    GLuint vertexArrayId;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programId;

    bool isInitialized;

    GameObject world;
    std::map<uint64_t, std::unique_ptr<GameObject>> gameObjects; // switch to unordered_map ?

    std::queue<uint64_t> destructionQueue;

    GameEngine();
    ~GameEngine();

    void destroyQueuedObjects();
};
