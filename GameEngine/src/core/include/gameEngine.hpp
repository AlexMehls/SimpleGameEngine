#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

// This class is a singleton
class GameEngine
{
public:
    static GameEngine &getInstance();

    int gameEngineInit();
    void gameEngineTerminate();

    GLFWwindow *window;

    GLuint vertexArrayId;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programId;
    GLuint mvpMatrixId;

    GameEngine(GameEngine const &) = delete;
    void operator=(GameEngine const &) = delete;

private:
    GameEngine();
    ~GameEngine();

    bool isInitialized;
};