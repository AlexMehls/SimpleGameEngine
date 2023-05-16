#include "rotationHelpers.hpp"

#include <glm/gtc/quaternion.hpp>

namespace RotationHelpers
{
    glm::vec3 eulerAnglesAlternateWrapping(glm::vec3 angles)
    {
        float pi = glm::pi<float>();
        float h_pi = glm::half_pi<float>();
        float two_pi = glm::two_pi<float>();

        if (angles.z < -h_pi || angles.z > h_pi)
        {
            angles.z += pi;
            if (angles.z > pi)
            {
                angles.z -= two_pi;
            }

            angles.y = pi - angles.y;
            if (angles.y > pi)
            {
                angles.y -= two_pi;
            }

            angles.x += pi;
            if (angles.x > pi)
            {
                angles.x -= two_pi;
            }
        }
        return angles;
    }
} // namespace RotationHelpers
