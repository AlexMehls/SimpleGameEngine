#pragma once

#include "component.hpp"
#include "transform.hpp"

#include <glm/glm.hpp>

class Collider : public Component
{
public:
    struct CollisionInfo
    {
        CollisionInfo(Collider *other) : otherCollider(other) {}

        Collider *otherCollider;
        glm::vec3 collisionPoint;
    };

    Transform transform;

    Collider(GameObject *parent);
    ~Collider();

    virtual std::string type() const override;
    virtual json getLevelParams() const override;
    virtual void loadParams(const json &params) override;

    virtual void saveState() override;
    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};
