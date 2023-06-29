#include "userInput.hpp"

#include "gameEngine.hpp"
#include "inputConfig.hpp"
#include "inputMappings.hpp"

#include <algorithm>

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

    mouseScrollX = mouseScrollX_akkum;
    mouseScrollY = mouseScrollY_akkum;
    mouseScrollX_akkum = 0;
    mouseScrollY_akkum = 0;

    return;
}

bool UserInput::loadConfig(const std::string &path)
{
    InputConfig config;
    if (!config.load(path))
    {
        return false;
    }
    actionMap = config.directActionMap;
    axisMap = config.directAxisMap;
    dualAxisMap = config.directDualAxisMap;

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
    mouseScrollX_akkum += deltaX;
    mouseScrollY_akkum += deltaY;
    return;
}

bool UserInput::getButton(const std::string &name)
{
    int button = InputMappings::nameToButton(name);
    if (button >= 0)
    {
        return getButton(button);
    }
    int scancode = InputMappings::nameToScancode(name);
    return pressedKeys.count(scancode);
}
bool UserInput::getButton(int glfwButton)
{
    if (InputMappings::isMouseButton(glfwButton))
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
    if (actionMap.contains(name))
    {
        return getButton(actionMap[name]);
    }
    return false;
}
double UserInput::getActionAxis(const std::string &name)
{
    if (actionMap.contains(name))
    {
        return getAxis(actionMap[name]);
    }
    else if (axisMap.contains(name))
    {
        auto buttons = axisMap[name];
        return getButton(buttons.first) - getButton(buttons.second);
    }
    return 0;
}
glm::vec2 UserInput::getActionDualAxis(const std::string &name)
{
    if (actionMap.contains(name))
    {
        return getDualAxis(actionMap[name]);
    }
    else if (axisMap.contains(name))
    {
        auto axes = axisMap[name];
        return glm::vec2(getAxis(axes.first), getAxis(axes.second));
    }
    else if (dualAxisMap.contains(name))
    {
        auto buttons = dualAxisMap[name];
        return glm::vec2(getButton(std::get<0>(buttons)) - getButton(std::get<1>(buttons)), getButton(std::get<2>(buttons)) - getButton(std::get<3>(buttons)));
    }
    return glm::vec2(0);
}
