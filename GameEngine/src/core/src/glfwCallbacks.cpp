#include "glfwCallbacks.hpp"

#include "userInput.hpp"
#include "gameEngine.hpp"

#include <iostream>

void error_callback(int error, const char *description)
{
    std::cerr << "Error " << error << ": " << description << std::endl;
    return;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    UserInput &input = UserInput::getInstance();

    if (action == GLFW_PRESS)
    {
        input.keyPressed(scancode);
        // std::cout << scancode << std::endl;
    }
    else if (action == GLFW_RELEASE)
    {
        input.keyReleased(scancode);
    }
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    return;
}

void cursor_position_callback(GLFWwindow *window, double xPos, double yPos)
{
    // std::cout << "Cursor Pos: " << xPos << ", " << yPos << std::endl;
    // glfwSetCursorPos(window, 0, 0);
}

void mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
    UserInput &input = UserInput::getInstance();

    if (action == GLFW_PRESS)
    {
        input.mousePressed(button);
        // std::cout << button << std::endl;
    }
    else if (action == GLFW_RELEASE)
    {
        input.mouseReleased(button);
    }
    return;
}

void scroll_callback(GLFWwindow *window, double deltaX, double deltaY)
{
    UserInput &input = UserInput::getInstance();
    input.mouseScrolled(deltaX, deltaY);
    return;
}

void window_focus_callback(GLFWwindow *window, int focused)
{
    if (focused && GameEngine::getInstance().cursorLocked())
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else
    {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
}
