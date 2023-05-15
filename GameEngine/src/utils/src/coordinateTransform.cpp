#include "coordinateTransform.hpp"

namespace CoordinateTransform
{
    glm::vec3 toOpenGlPos(const glm::vec3 &toConvert)
    {
        return glm::vec3(toConvert.x, toConvert.z, -toConvert.y);
    }
    glm::vec3 toOpenGlScale(const glm::vec3 &toConvert)
    {
        return glm::vec3(toConvert.x, toConvert.z, toConvert.y);
    }

    glm::vec3 toGamePos(const glm::vec3 &toConvert)
    {
        return glm::vec3(toConvert.x, -toConvert.z, toConvert.y);
    }
    glm::vec3 toGameScale(const glm::vec3 &toConvert)
    {
        return glm::vec3(toConvert.x, toConvert.z, toConvert.y);
    }
} // namespace CoordinateTransform
