#pragma once

#include "collider.hpp"

namespace CollisionDetection
{
    // Not accurate
    bool collisionSpheroids(const Collider &collider, const Collider &colliderOther, Collider::CollisionInfo &info);
    bool collisionSpheres(const Collider &collider, const Collider &colliderOther, Collider::CollisionInfo &info);
} // namespace CollisionDetection
