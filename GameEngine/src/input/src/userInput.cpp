#include "userInput.hpp"

#include "gameEngine.hpp"

#include <algorithm>
#include <sstream>

#include <iostream>

UserInput &UserInput::getInstance()
{
    static UserInput userInput;
    return userInput;
}

void UserInput::step()
{
    GameEngine &engine = GameEngine::getInstance();

    double mouseX, mouseY;
    glfwGetCursorPos(engine.window, &mouseX, &mouseY);

    mouseDeltaX = mouseX - prevMouseX;
    mouseDeltaY = mouseY - prevMouseY;
    if (skipNextMouseInput)
    {
        skipNextMouseInput = false;
        mouseDeltaX = 0;
        mouseDeltaY = 0;
    }

    prevMouseX = mouseX;
    prevMouseY = mouseY;

    mouseScrollX = 0;
    mouseScrollY = 0;

    return;
}

bool UserInput::loadConfig(const std::string &path)
{
    // TODO
    return true;
}

void UserInput::keyPressed(int scancode)
{
    pressedKeys.insert(scancode);
    return;
}
void UserInput::keyReleased(int scancode)
{
    pressedKeys.erase(scancode);
    return;
}
void UserInput::mousePressed(int button)
{
    pressedMouseButtons.insert(button);
    return;
}
void UserInput::mouseReleased(int button)
{
    pressedMouseButtons.erase(button);
    return;
}
void UserInput::mouseScrolled(double deltaX, double deltaY)
{
    mouseScrollX += deltaX;
    mouseScrollY += deltaY;
    return;
}

bool UserInput::getButton(const std::string &name)
{
    std::string upperName = name;
    std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });

    const std::string MOUSE_PREFIX = "MOUSE_";
    const std::string SCANCODE_PREFIX = "CODE_";

    // "simple" keys (e.g "A", "0")
    if (upperName.size() == 1)
    {
        // GLFW keys use ascii codes for alphanumerical keys
        int button = char(upperName[0]);
        int scancode = glfwGetKeyScancode(button);
        return pressedKeys.count(scancode);
    }
    // mouse buttons
    else if (upperName.size() > MOUSE_PREFIX.size() && upperName.compare(0, MOUSE_PREFIX.size(), MOUSE_PREFIX) == 0)
    {
        // GLFW mouse buttons are numbered 0-7
        std::istringstream nameStream(upperName.substr(MOUSE_PREFIX.size()));
        int button;
        nameStream >> button;
        --button;
        return pressedMouseButtons.count(button);
    }
    // scancodes (for non-named keys)
    else if (upperName.size() > SCANCODE_PREFIX.size() && upperName.compare(0, SCANCODE_PREFIX.size(), SCANCODE_PREFIX) == 0)
    {
        std::istringstream nameStream(upperName.substr(SCANCODE_PREFIX.size()));
        int scancode;
        nameStream >> scancode;
        return pressedKeys.count(scancode);
    }
    // other keys (e.g. "CTRL", "SHIFT")
    else
    {
        if (upperName == "SPACE")
        {
            return getButton(GLFW_KEY_SPACE);
        }
        else if (upperName == "CTRL")
        {
            return getButton(GLFW_KEY_LEFT_CONTROL);
        }
        else if (upperName == "SHIFT")
        {
            return getButton(GLFW_KEY_LEFT_SHIFT);
        }
        else if (upperName == "ALT")
        {
            return getButton(GLFW_KEY_LEFT_ALT);
        }
        else if (upperName == "TAB")
        {
            return getButton(GLFW_KEY_TAB);
        }
        // TODO: more
    }
    return false;
}
bool UserInput::getButton(int glfwButton)
{
    if (glfwButton >= 0 && glfwButton < 8)
    {
        return pressedMouseButtons.count(glfwButton);
    }
    int scancode = glfwGetKeyScancode(glfwButton);
    return pressedKeys.count(scancode);
}
double UserInput::getAxis(const std::string &name)
{
    std::string upperName = name;
    std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });

    if (upperName == "MOUSE_X")
    {
        return mouseDeltaX;
    }
    else if (upperName == "MOUSE_Y")
    {
        return mouseDeltaY;
    }
    else if (upperName == "MOUSE_SCROLL_X")
    {
        return mouseScrollX;
    }
    else if (upperName == "MOUSE_SCROLL_Y" || upperName == "MOUSE_SCROLL")
    {
        return mouseScrollY;
    }

    return 0;
}
glm::vec2 UserInput::getDualAxis(const std::string &name)
{
    std::string upperName = name;
    std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                   [](unsigned char c)
                   { return std::toupper(c); });

    if (upperName == "MOUSE")
    {
        return glm::vec2(mouseDeltaX, mouseDeltaY);
    }
    else if (upperName == "MOUSE_SCROLL")
    {
        return glm::vec2(mouseScrollX, mouseScrollY);
    }

    return glm::vec2(0);
}

bool UserInput::getAction(const std::string &name)
{
    return getButton(actionToButtonMap[name]);
}
double UserInput::getActionAxis(const std::string &name)
{
    return getAxis(actionToButtonMap[name]);
}
glm::vec2 UserInput::getActionDualAxis(const std::string &name)
{
    return getDualAxis(actionToButtonMap[name]);
}
