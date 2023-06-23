#include "collisionDetection.hpp"

#include <cmath>
#include <glm/glm.hpp>

namespace CollisionDetection
{
    bool collisionSpheroids(const Collider &collider, const Collider &colliderOther, Collider::CollisionInfo &info)
    {
        // Not accurate

        glm::vec3 pos1 = collider.transform.getPos();
        glm::vec3 pos2 = colliderOther.transform.getPos();
        glm::quat rot1 = collider.transform.getRot();
        glm::quat rot2 = colliderOther.transform.getRot();
        glm::vec3 scale1 = collider.transform.getScale();
        glm::vec3 scale2 = colliderOther.transform.getScale();

        glm::vec3 direction1 = pos2 - pos1;
        glm::vec3 direction2 = pos1 - pos2;
        float distance = glm::length(direction1);

        direction1 = glm::conjugate(rot1) * direction1;
        direction2 = glm::conjugate(rot2) * direction2;

        direction1 /= scale1;
        direction1 = glm::normalize(direction1);
        direction1 *= scale1;
        float radius1 = glm::length(direction1);

        direction2 /= scale2;
        direction2 = glm::normalize(direction2);
        direction2 *= scale2;
        float radius2 = glm::length(direction2);

        if (distance <= radius1 + radius2)
        {
            info.collisionPoint = rot1 * direction1 + pos1;
            return true;
        }
        return false;
    }

    bool collisionSpheres(const Collider &collider, const Collider &colliderOther, Collider::CollisionInfo &info)
    {
        glm::vec3 pos1 = collider.transform.getPos();
        glm::vec3 pos2 = colliderOther.transform.getPos();
        glm::vec3 scale1 = collider.transform.getScale();
        glm::vec3 scale2 = colliderOther.transform.getScale();

        glm::vec3 direction1 = pos2 - pos1;
        float distance = glm::length(direction1);

        float radius1 = (scale1.x + scale1.y + scale1.z) / 3;
        float radius2 = (scale2.x + scale2.y + scale2.z) / 3;

        if (distance <= radius1 + radius2)
        {
            info.collisionPoint = direction1 + pos1;
            return true;
        }
        return false;
    }
} // namespace CollisionDetection
