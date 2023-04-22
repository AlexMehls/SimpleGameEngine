#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

class GameEngine
{
public:
    GameEngine();
    ~GameEngine();

    static GameEngine &getInstance();

    GLFWwindow *window;

    GLuint vertexArrayId;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint programId;
    GLuint mvpMatrixId;

private:
    int gameEngineInit();
    void gameEngineTerminate();
};