#pragma once

#include "gameObject.hpp"
#include "idGenerator.hpp"

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
    GLFWwindow *window;

    GLuint vertexArrayId;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programId;
    GLuint mvpMatrixId;

    static GameEngine &getInstance();

    int gameEngineInit();
    void gameEngineTerminate();

    GameObject &createGameObject();
    void destroyGameObject(GameObject &toDestroy);

    void update(double deltaTime);
    void fixedUpdate(double deltaTime);

    GameEngine(GameEngine const &) = delete;
    void operator=(GameEngine const &) = delete;

private:
    GameEngine();
    ~GameEngine();

    void destroyQueuedObjects();

    bool isInitialized;

    GameObject world;
    std::map<uint64_t, std::unique_ptr<GameObject>> gameObjects; // switch to unordered_map ?

    std::queue<uint64_t> destructionQueue;
};
