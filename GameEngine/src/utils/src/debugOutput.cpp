#include "debugOutput.hpp"

#include <iostream>

namespace DebugOutput
{
    void printVec(const glm::vec3 &vec)
    {
        std::cout << "[DEBUG VEC]: X: " << vec.x << ", Y: " << vec.y << ", Z: " << vec.z << std::endl;
    }
} // namespace DebugOutput
