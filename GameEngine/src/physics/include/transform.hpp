#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
public:
    Transform();

    // Returns position in world-space in x, y, z
    glm::vec3 getPos() const;
    // Returns rotation in world-space as quaternion
    glm::quat getRot() const;
    // Returns rotation in world-space in pitch, yaw, roll
    glm::vec3 getEulerAngles() const;
    // Returns scale in world-space in x, y, z
    glm::vec3 getScale() const;

    // Returns position in local space in x, y, z
    const glm::vec3 &getLocalPos() const;
    // Returns rotation in local space as quaternion
    const glm::quat &getLocalRot() const;
    // Returns rotation in local space in pitch, yaw, roll
    glm::vec3 getLocalEulerAngles() const;
    // Returns scale in local space in x, y, z
    const glm::vec3 &getLocalScale() const;

    // Sets position in world-space in x, y, z
    void setPos(const glm::vec3 &pos);
    // Sets rotation in world-space as quaternion
    void setRot(const glm::quat &rot);
    // Sets rotation in world-space in pitch, yaw, roll
    void setEulerAngles(const glm::vec3 &angles);
    // Sets scale in world-space in x, y, z
    void setScale(const glm::vec3 &scale);

    // Sets position in local space in x, y, z
    void setLocalPos(const glm::vec3 &pos);
    // Sets rotation in local space as quaternion
    void setLocalRot(const glm::quat &rot);
    // Sets rotation in local space in pitch, yaw, roll
    void setLocalEulerAngles(const glm::vec3 &angles);
    // Sets scale in local space in x, y, z
    void setLocalScale(const glm::vec3 &scale);

    // Moves by deltaPos in x, y, z
    void move(const glm::vec3 &deltaPos);
    // Rotates by deltaAngles in pitch, yaw, roll
    void rotate(const glm::vec3 &deltaAngles);
    // Scales by deltaScale in x, y, z
    void scale(const glm::vec3 &deltaScale);
    // Sets forward direction towards target
    void lookAt(const glm::vec3 &targetPos);

    // Updates the previous values with the current values
    void savePreviousState();

    // Sets a new parent while keeping global values the same
    void setParent(const Transform &other);

    // Model matrix with interpolation for rendering (1 = only current values)
    glm::mat4 getModelMat(float interpolation) const;

private:
    // Current values (locals)

    glm::vec3 position;
    glm::quat rotation;
    glm::vec3 m_scale; // different name, to avoid name conflict with method

    // Previous values (globals)

    glm::vec3 prev_position;
    glm::quat prev_rotation;
    glm::vec3 prev_scale;

    const Transform *parent; // couple to gameObject / component parent?
};
