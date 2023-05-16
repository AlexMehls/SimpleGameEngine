#pragma once

#include <glm/glm.hpp>

namespace RotationHelpers
{
    // EXPERIMENTAL
    // Changes the wrapping for euler angles of a quaternion with pitch, yaw, roll in radians
    // to where roll is limited to (-pi/2, pi/2) and pitch / yaw limited to (-pi, pi)
    glm::vec3 eulerAnglesAlternateWrapping(glm::vec3 angles);
} // namespace RotationHelpers
