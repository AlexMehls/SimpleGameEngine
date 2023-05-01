#include "transform.hpp"

Transform::Transform()
{
    position = glm::vec3(0);
    rotation = glm::quat(1, 0, 0, 0);
    scale = glm::vec3(0);

    savePreviousState();

    return;
}

// GLOBAL GETTERS

// Returns position in world-space in x, y, z
const glm::vec3 &Transform::getPos() const
{
    if (parent == nullptr)
    {
        return position;
    }
    return position + parent->getPos();
}
// Returns rotation in world-space as quaternion
const glm::quat &Transform::getRot() const
{
    if (parent == nullptr)
    {
        return rotation;
    }
    return rotation * parent->getRot();
}
// Returns rotation in world-space in pitch, yaw, roll
glm::vec3 Transform::getEulerAngles() const
{
    return glm::eulerAngles(getRot());
}
// Returns scale in world-space in x, y, z
const glm::vec3 &Transform::getScale() const
{
    if (parent == nullptr)
    {
        return scale;
    }
    return scale * parent->getScale();
}

// LOCAL GETTERS

// Returns position in local space in x, y, z
const glm::vec3 &Transform::getLocalPos() const
{
    return position;
}
// Returns rotation in local space as quaternion
const glm::quat &Transform::getLocalRot() const
{
    return rotation;
}
// Returns rotation in local space in pitch, yaw, roll
glm::vec3 Transform::getLocalEulerAngles() const
{
    return glm::eulerAngles(rotation);
}
// Returns scale in local space in x, y, z
const glm::vec3 &Transform::getLocalScale() const
{
    return scale;
}

// GLOBAL SETTERS

// Sets position in world-space in x, y, z
void Transform::setPos(const glm::vec3 &pos)
{
    if (parent == nullptr)
    {
        position = pos;
    }
    else
    {
        position = pos - parent->getPos();
    }
    return;
}
// Sets rotation in world-space as quaternion
void Transform::setRot(const glm::quat &rot)
{
    if (parent == nullptr)
    {
        rotation = rot;
    }
    else
    {
        rotation = rot * glm::conjugate(parent->getRot());
    }
    return;
}
// Sets rotation in world-space in pitch, yaw, roll
void Transform::setEulerAngles(const glm::vec3 &angles)
{
    setRot(glm::quat(angles));
    return;
}
// Sets scale in world-space in x, y, z
void Transform::setScale(const glm::vec3 &scale)
{
    if (parent == nullptr)
    {
        Transform::scale = scale;
    }
    else
    {
        Transform::position = scale / parent->getScale();
    }
    return;
}

// LOCAL SETTERS

// Sets position in local space in x, y, z
void Transform::setLocalPos(const glm::vec3 &pos)
{
    position = pos;
    return;
}
// Sets rotation in local space as quaternion
void Transform::setLocalRot(const glm::quat &rot)
{
    rotation = rot;
    return;
}
// Sets rotation in local space in pitch, yaw, roll
void Transform::setLocalEulerAngles(const glm::vec3 &angles)
{
    rotation = glm::quat(angles);
    return;
}
// Sets scale in local space in x, y, z
void Transform::setLocalScale(const glm::vec3 &scale)
{
    Transform::scale = scale;
    return;
}

// Updates the previous values with the current values
void Transform::savePreviousState()
{
    prev_position = position;
    prev_rotation = rotation;
    prev_scale = scale;

    return;
}
