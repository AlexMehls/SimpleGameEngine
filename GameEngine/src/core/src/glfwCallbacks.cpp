#include "glfwCallbacks.hpp"

#include "userInput.hpp"

#include <iostream>

void error_callback(int error, const char *description)
{
    std::cerr << "Error " << error << ": " << description << std::endl;
    return;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
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