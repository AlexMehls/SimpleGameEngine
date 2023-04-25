#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    Transform();

    const glm::vec3 &getPos() const;
    const glm::quat &getRot() const;
    glm::vec3 getEulerAngles() const;
    const glm::vec3 &getScale() const;

    const glm::vec3 &getLocalPos() const;
    const glm::quat &getLocalRot() const;
    glm::vec3 getLocalEulerAngles() const;
    const glm::vec3 &getLocalScale() const;

    void setPos(const glm::vec3 &pos);
    void setRot(const glm::quat &rot);
    void setEulerAngles(const glm::vec3 &angles);
    void setScale(const glm::vec3 &scale);

    void setLocalPos(const glm::vec3 &pos);
    void setLocalRot(const glm::quat &rot);
    void setLocalEulerAngles(const glm::vec3 &angles);
    void setLocalScale(const glm::vec3 &scale);

    // Set prev variables to current values
    void update(); // name change?

    // Model matrix with interpolation for rendering
    const glm::mat4 &getModelMat(double interpolation) const;

private:
    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 scale; // best type?

    glm::vec3 prev_position;
    glm::quat prev_rotation;
    glm::vec3 prev_scale; // best type?

    Transform *parent; // couple to gameObject / component parent?
};
