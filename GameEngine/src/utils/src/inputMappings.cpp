#include "inputMappings.hpp"

#include <algorithm>
#include <sstream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace InputMappings
{
    int nameToScancode(const std::string &name)
    {
        std::string upperName = name;
        std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                       [](unsigned char c)
                       { return std::toupper(c); });

        // scancodes (for non-named keys)
        if (upperName.size() > SCANCODE_PREFIX.size() && upperName.compare(0, SCANCODE_PREFIX.size(), SCANCODE_PREFIX) == 0)
        {
            std::istringstream nameStream(upperName.substr(SCANCODE_PREFIX.size()));
            int scancode;
            nameStream >> scancode;
            return scancode;
        }

        int button = nameToButton(name);
        if (button >= 0)
        {
            return glfwGetKeyScancode(button);
        }
        return -1;
    }

    int nameToButton(const std::string &name)
    {
        std::string upperName = name;
        std::transform(upperName.begin(), upperName.end(), upperName.begin(),
                       [](unsigned char c)
                       { return std::toupper(c); });

        // "simple" keys (e.g "A", "0")
        if (upperName.size() == 1)
        {
            // GLFW keys use ascii codes for alphanumerical keys
            return char(upperName[0]);
        }
        // mouse buttons
        else if (upperName.size() > MOUSE_PREFIX.size() && upperName.compare(0, MOUSE_PREFIX.size(), MOUSE_PREFIX) == 0)
        {
            // GLFW mouse buttons are numbered 0-7
            std::istringstream nameStream(upperName.substr(MOUSE_PREFIX.size()));
            int button;
            nameStream >> button;
            return button - 1;
        }
        // other keys (e.g. "CTRL", "SHIFT")
        else
        {
            if (upperName == "SPACE")
            {
                return GLFW_KEY_SPACE;
            }
            else if (upperName == "CTRL")
            {
                return GLFW_KEY_LEFT_CONTROL;
            }
            else if (upperName == "SHIFT")
            {
                return GLFW_KEY_LEFT_SHIFT;
            }
            else if (upperName == "ALT")
            {
                return GLFW_KEY_LEFT_ALT;
            }
            else if (upperName == "TAB")
            {
                return GLFW_KEY_TAB;
            }
            // TODO: more
        }
        return -1;
    }

    std::string buttonToName(int button)
    {
        std::string name;

        // "simple" keys (e.g "A", "0")
        if ((button >= 48 && button <= 57) || (button >= 65 && button <= 90))
        {
            // GLFW keys use ascii codes for alphanumerical keys
            name = (char)button;
        }
        // mouse buttons
        else if (button >= 0 && button <= 7)
        {
            // GLFW mouse buttons are numbered 0-7
            name = MOUSE_PREFIX + std::to_string(button + 1);
        }
        // other keys (e.g. "CTRL", "SHIFT")
        else
        {
            switch (button)
            {
            case GLFW_KEY_SPACE:
                name = "SPACE";
                break;
            case GLFW_KEY_LEFT_CONTROL:
                name = "CTRL";
                break;
            case GLFW_KEY_LEFT_SHIFT:
                name = "SHIFT";
                break;
            case GLFW_KEY_LEFT_ALT:
                name = "ALT";
                break;
            case GLFW_KEY_TAB:
                name = "TAB";
                break;
            default:
                break;
            }
            // TODO: more
        }
        return name;
    }

    bool isMouseButton(int button)
    {
        return button >= 0 && button < 8;
    }

    bool isPrimitive(const std::string &name)
    {
        return (nameToButton(name) != -1 || nameToScancode(name) != -1);
    }
} // namespace InputMappings
