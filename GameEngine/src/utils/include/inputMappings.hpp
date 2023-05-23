#pragma once

#include <string>

namespace InputMappings
{
    const std::string SCANCODE_PREFIX = "CODE_";
    const std::string MOUSE_PREFIX = "MOUSE_";

    // Returns scancode (only for keys) or -1 if name invalid
    int nameToScancode(const std::string &name);
    // Returns glfwButton number or -1 if name invalid
    int nameToButton(const std::string &name);
    // Returns the button name for a glfwButton
    std::string buttonToName(int button);

    // Returns true if the glfwButton is a mouse button
    bool isMouseButton(int button);

    // Returns true if the button, axis or dualAxis is pre-defined
    bool isPrimitive(const std::string &name);
} // namespace InputMappings
