#include "shader.hpp"
#include "primitiveObjects.hpp"
#include "camera.hpp"
#include "userInput.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <filesystem>
#include <chrono>

void error_callback(int error, const char *description)
{
    std::cerr << "Error " << error << ": " << description << std::endl;
    return;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

static void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
{
    // std::cout << "Cursor Pos: " << xPos << ", " << yPos << std::endl;

    UserInput &input = UserInput::getInstance();

    // Should this be done differently?
    input.mouseDeltaX += xPos - input.mouseX;
    input.mouseDeltaY += yPos - input.mouseY;
    input.mouseX = xPos;
    input.mouseY = yPos;
    // glfwSetCursorPos(window, 0, 0);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        std::cout << "Pressed Left Mouse Button!" << std::endl;
    }
}

void scroll_callback(GLFWwindow *window, double xOffset, double yOffset)
{
}

int main(int argc, char *argv[])
{
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

    GLFWwindow *window = glfwCreateWindow(640, 480, "Game Test", NULL, NULL);
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

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
    {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);

    GLuint colorbuffer;
    glGenBuffers(1, &colorbuffer);

    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path shaderFolder = projectFolder / "GameEngine/src/rendering/shaders";
    std::string vertexShaderPath = shaderFolder.string() + "/SimpleVertexShader.vertexshader";
    std::string fragmentShaderPath = shaderFolder.string() + "/SimpleFragmentShader.fragmentshader";

    GLuint programID = LoadShaders(vertexShaderPath.c_str(), fragmentShaderPath.c_str());
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    glClearColor(0.5f, 0.5f, 0.5f, 0.0f);

    Triangle triangle;
    triangle.setPos(glm::vec3(2, 0, 0));

    Cube cube;

    Plane plane;
    plane.setPos(glm::vec3(0, -1.5f, 1));

    Camera camera(vertexbuffer, colorbuffer, MatrixID);
    camera.setPos(glm::vec3(0, 2, 5));
    camera.lookAt(glm::vec3(0));
    float speed = 1;
    float mouseSpeed = 0.0005f;

    int cameraMoveDirection = 1;
    float cameraMoveSpeed = 1;

    float ratio;
    int width, height;
    UserInput &input = UserInput::getInstance();

    double prevTime = glfwGetTime();
    double curTime;
    double deltaTime;
    double fps;

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

    glUseProgram(programID);

    while (!glfwWindowShouldClose(window))
    {
        curTime = glfwGetTime();
        deltaTime = curTime - prevTime;
        prevTime = curTime;

        fps = 1 / deltaTime;
        // std::cout << fps << std::endl;

        glfwGetFramebufferSize(window, &width, &height);
        ratio = width / (float)height;
        // Setting a fixed resolution causes stretching if window shape changes
        camera.setRatio(ratio);

        camera.rotate(mouseSpeed * input.mouseDeltaX,
                      mouseSpeed * input.mouseDeltaY);

        /*
        camera.move(glm::vec3(deltaTime * cameraMoveSpeed * cameraMoveDirection, 0, 0));
        if (camera.getPos().x >= 5)
        {
            cameraMoveDirection = -1;
        }
        else if (camera.getPos().x <= -5)
        {
            cameraMoveDirection = 1;
        }
        camera.lookAt(glm::vec3(0));
        */

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.draw(cube);
        camera.draw(triangle);
        camera.draw(plane);

        glfwSwapBuffers(window);
        input.step();
        glfwPollEvents();
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &colorbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);

    glfwDestroyWindow(window);

    glfwTerminate();

    return 0;
}