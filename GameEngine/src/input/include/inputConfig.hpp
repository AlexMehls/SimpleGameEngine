#pragma once

#include <map>
#include <string>

class InputConfig
{
public:
    // For action -> button / axis / dualAxis
    std::map<std::string, std::string> directActionMap;
    // For action -> 2 buttons / 2 axes
    std::map<std::string, std::pair<std::string, std::string>> directAxisMap;
    // For action -> 4 buttons
    std::map<std::string, std::tuple<std::string, std::string, std::string, std::string>> directDualAxisMap;

    // Adds mapping action -> known button / axis / dualAxis
    void setButton(const std::string &action, const std::string &name);
    // Adds mapping action -> button
    // Scancode is used if glfwButton is invalid
    void setButton(const std::string &action, int glfwButton, int scancode);
    // Adds mapping action(axis) -> action+, action-
    // action+ / action- can be known buttons
    void setAxis(const std::string &action, const std::string &positive, const std::string &negative);
    // Adds mapping action(axis) -> axis
    void setAxis(const std::string &action, const std::string &axis);
    // Adds mapping action(dualAxis) -> action(axisX), action(axisY)
    // axisX / axisY can be known axes
    void setDualAxis(const std::string &action, const std::string &axisX, const std::string &axisY);
    // Adds mapping action(dualAxis) -> dualAxis
    void setDualAxis(const std::string &action, const std::string &dualAxis);
    // Removes action mapping
    void remove(const std::string &action);

    bool load(const std::string &path);
    bool save(const std::string &path);

    // Generates the direct maps
    // Returns true if successful
    bool parseDirectMaps();

private:
    // For action -> button
    std::map<std::string, std::string> actionMap;
    // For axis -> 2 buttons / actions
    std::map<std::string, std::pair<std::string, std::string>> axisActionsMap;
    // For axis -> axis
    std::map<std::string, std::string> axisMap;
    // For dualAxis -> 2 axes
    std::map<std::string, std::pair<std::string, std::string>> dualAxisAxesMap;
    // For dualAxis -> dualAxis
    std::map<std::string, std::string> dualAxisMap;
};
