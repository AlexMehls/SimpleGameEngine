#pragma once

#include <glm/glm.hpp>

namespace CoordinateTransform
{
    glm::vec3 toOpenGlPos(const glm::vec3 &toConvert);
    glm::vec3 toOpenGlScale(const glm::vec3 &toConvert);
} // namespace CoordinateTransform
