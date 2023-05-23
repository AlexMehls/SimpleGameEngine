#include "inputConfig.hpp"

#include "inputMappings.hpp"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

using json = nlohmann::json;

void InputConfig::setButton(const std::string &action, const std::string &name)
{
    actionMap[action] = name;
    return;
}
void InputConfig::setButton(const std::string &action, int glfwButton, int scancode)
{
    if (glfwButton != GLFW_KEY_UNKNOWN)
    {
        actionMap[action] = InputMappings::buttonToName(glfwButton);
        return;
    }
    actionMap[action] = InputMappings::SCANCODE_PREFIX + std::to_string(scancode);
    return;
}
void InputConfig::setAxis(const std::string &action, const std::string &positive, const std::string &negative)
{
    axisActionsMap[action] = std::pair<std::string, std::string>(positive, negative);
    return;
}
void InputConfig::setAxis(const std::string &action, const std::string &axis)
{
    axisMap[action] = axis;
    return;
}
void InputConfig::setDualAxis(const std::string &action, const std::string &axisX, const std::string &axisY)
{
    dualAxisAxesMap[action] = std::pair<std::string, std::string>(axisX, axisY);
    return;
}
void InputConfig::setDualAxis(const std::string &action, const std::string &dualAxis)
{
    dualAxisMap[action] = dualAxis;
    return;
}
void InputConfig::remove(const std::string &action)
{
    actionMap.erase(action);
    axisActionsMap.erase(action);
    axisMap.erase(action);
    dualAxisAxesMap.erase(action);
    dualAxisMap.erase(action);
    return;
}

bool InputConfig::load(const std::string &path)
{
    std::ifstream f(path);
    json config = json::parse(f);

    actionMap.clear();
    axisActionsMap.clear();
    axisMap.clear();
    dualAxisAxesMap.clear();
    dualAxisMap.clear();

    for (auto &[key, value] : config["buttons"].items())
    {
        if (value.is_string())
        {
            actionMap[key] = value;
        }
        else
        {
            std::cerr << "InputConfig: Couldn't load value: " << value.dump() << " for key: " << key << std::endl;
        }
    }

    for (auto &[key, value] : config["axes"].items())
    {
        if (value.is_string())
        {
            axisMap[key] = value;
        }
        else if (value.is_array() && value.size() == 2)
        {
            axisActionsMap[key] = std::pair<std::string, std::string>(value[0], value[1]);
        }
        else
        {
            std::cerr << "InputConfig: Couldn't load value: " << value.dump() << " for key: " << key << std::endl;
        }
    }

    for (auto &[key, value] : config["dualAxes"].items())
    {
        if (value.is_string())
        {
            dualAxisMap[key] = value;
        }
        else if (value.is_array() && value.size() == 2)
        {
            dualAxisAxesMap[key] = std::pair<std::string, std::string>(value[0], value[1]);
        }
        else
        {
            std::cerr << "InputConfig: Couldn't load value: " << value.dump() << " for key: " << key << std::endl;
        }
    }

    return parseDirectMaps();
}
bool InputConfig::save(const std::string &path)
{
    json config;

    for (auto &element : actionMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        config["buttons"][action] = mappedValue;
    }

    for (auto &element : axisActionsMap)
    {
        std::string action = element.first;
        std::string mappedValue1 = element.second.first;
        std::string mappedValue2 = element.second.second;

        config["axes"][action] = {mappedValue1, mappedValue2};
    }

    for (auto &element : axisMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        config["axes"][action] = mappedValue;
    }

    for (auto &element : dualAxisAxesMap)
    {
        std::string action = element.first;
        std::string mappedValue1 = element.second.first;
        std::string mappedValue2 = element.second.second;

        config["dualAxes"][action] = {mappedValue1, mappedValue2};
    }

    for (auto &element : dualAxisMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        config["dualAxes"][action] = mappedValue;
    }

    std::ofstream f(path);
    f << std::setw(4) << config << std::endl;

    return true;
}

bool InputConfig::parseDirectMaps()
{
    const int MAX_RECURSION_DEPTH = 10;

    // Resolve button aliases
    for (auto &element : actionMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        int depth = 0;
        while (actionMap.contains(mappedValue))
        {
            mappedValue = actionMap[mappedValue];

            ++depth;
            if (depth >= MAX_RECURSION_DEPTH)
            {
                std::cerr << "InputConfig: Max recursion depth exceeded while parsing actions" << std::endl;
                return false;
            }
        }
        directActionMap[action] = mappedValue;
    }

    // Resolve axis -> button mapping
    for (auto &element : axisActionsMap)
    {
        std::string action = element.first;
        std::string mappedValue1 = element.second.first;
        std::string mappedValue2 = element.second.second;

        if (directActionMap.contains(mappedValue1))
        {
            mappedValue1 = directActionMap[mappedValue1];
        }
        if (directActionMap.contains(mappedValue2))
        {
            mappedValue2 = directActionMap[mappedValue2];
        }
        directAxisMap[action] = std::pair<std::string, std::string>(mappedValue1, mappedValue2);
    }

    // Resolve axis aliases
    for (auto &element : axisMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        int depth = 0;
        while (axisMap.contains(mappedValue))
        {
            mappedValue = axisMap[mappedValue];

            ++depth;
            if (depth >= MAX_RECURSION_DEPTH)
            {
                std::cerr << "InputConfig: Max recursion depth exceeded while parsing axes" << std::endl;
                return false;
            }
        }
        if (directAxisMap.contains(mappedValue))
        {
            directAxisMap[action] = directAxisMap[mappedValue];
        }
        else
        {
            directActionMap[action] = mappedValue;
        }
    }

    // Resolve dualAxis -> axis mapping
    for (auto &element : dualAxisAxesMap)
    {
        std::string action = element.first;
        std::string mappedValue1 = element.second.first;
        std::string mappedValue2 = element.second.second;

        if (directAxisMap.contains(mappedValue1) && directAxisMap.contains(mappedValue2))
        {
            std::pair<std::string, std::string> axisX = directAxisMap[mappedValue1];
            std::pair<std::string, std::string> axisY = directAxisMap[mappedValue2];
            directDualAxisMap[action] = std::tuple<std::string, std::string, std::string, std::string>(axisX.first, axisX.second, axisY.first, axisY.second);
        }
        else
        {
            directAxisMap[action] = std::pair<std::string, std::string>(mappedValue1, mappedValue2);
        }
    }

    // Resolve dualAxis aliases
    for (auto &element : dualAxisMap)
    {
        std::string action = element.first;
        std::string mappedValue = element.second;

        int depth = 0;
        while (dualAxisMap.contains(mappedValue))
        {
            mappedValue = dualAxisMap[mappedValue];

            ++depth;
            if (depth >= MAX_RECURSION_DEPTH)
            {
                std::cerr << "InputConfig: Max recursion depth exceeded while parsing dualAxes" << std::endl;
                return false;
            }
        }
        if (directDualAxisMap.contains(mappedValue))
        {
            directDualAxisMap[action] = directDualAxisMap[mappedValue];
        }
        else
        {
            directActionMap[action] = mappedValue;
        }
    }
    return true;
}
