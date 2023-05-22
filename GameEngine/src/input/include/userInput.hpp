#pragma once

#include <glm/glm.hpp>
#include <string>
#include <map>
#include <set>

#include <float.h>

// This class is a singleton
class UserInput
{
public:
    static UserInput &getInstance();

    void step();

    bool loadConfig(const std::string &path);

    void keyPressed(int scancode);
    void keyReleased(int scancode);
    void mousePressed(int button);
    void mouseReleased(int button);
    void mouseScrolled(double deltaX, double deltaY);

    // Returns true if the button is pressed (e.g. "a", "mouse_1")
    // Not all named keys may be available. In that case use the overload using GLFW keys or scancodes.
    bool getButton(const std::string &name);
    // Returns true if the button is pressed (e.g. GLFW_KEY_SPACE)
    bool getButton(int glfwButton);
    // Returns the value of the axis (e.g. "mouse_x")
    double getAxis(const std::string &name);
    // Returns the value of two related axes (e.g. "mouse")
    glm::vec2 getDualAxis(const std::string &name);

    // Returns true if the action (as specified in the config) is triggered
    bool getAction(const std::string &name);
    // Returns the value of the action axis (as specified in the config)
    double getActionAxis(const std::string &name);
    // Returns the value of two related action axes (as specified in the config)
    glm::vec2 getActionDualAxis(const std::string &name);

    UserInput(UserInput const &) = delete;
    void operator=(UserInput const &) = delete;

private:
    std::map<std::string, std::string> actionToButtonMap;

    // Buttons
    std::set<int> pressedKeys;
    std::set<int> pressedMouseButtons;
    // Axes
    double mouseDeltaX = 0;
    double mouseDeltaY = 0;
    double mouseScrollX = 0;
    double mouseScrollY = 0;

    double prevMouseX = 0;
    double prevMouseY = 0;
    bool skipNextMouseInput = true;

    UserInput() = default;
};
