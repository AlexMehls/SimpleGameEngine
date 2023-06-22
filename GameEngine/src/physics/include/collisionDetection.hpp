#pragma once

#include "collider.hpp"

namespace CollisionDetection
{
    bool collisionSpheroids(const Collider &collider, const Collider &colliderOther, Collider::CollisionInfo &info);
} // namespace CollisionDetection
