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

glm::vec3 Transform::getPos() const
{
    if (parent == nullptr)
    {
        return position;
    }
    return position + parent->getPos();
}
glm::quat Transform::getRot() const
{
    if (parent == nullptr)
    {
        return rotation;
    }
    return rotation * parent->getRot();
}
glm::vec3 Transform::getEulerAngles() const
{
    return glm::eulerAngles(getRot());
}
glm::vec3 Transform::getScale() const
{
    if (parent == nullptr)
    {
        return scale;
    }
    return scale * parent->getScale();
}

// LOCAL GETTERS

const glm::vec3 &Transform::getLocalPos() const
{
    return position;
}
const glm::quat &Transform::getLocalRot() const
{
    return rotation;
}
glm::vec3 Transform::getLocalEulerAngles() const
{
    return glm::eulerAngles(rotation);
}
const glm::vec3 &Transform::getLocalScale() const
{
    return scale;
}

// GLOBAL SETTERS

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
void Transform::setEulerAngles(const glm::vec3 &angles)
{
    setRot(glm::quat(angles));
    return;
}
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

void Transform::setLocalPos(const glm::vec3 &pos)
{
    position = pos;
    return;
}
void Transform::setLocalRot(const glm::quat &rot)
{
    rotation = rot;
    return;
}
void Transform::setLocalEulerAngles(const glm::vec3 &angles)
{
    rotation = glm::quat(angles);
    return;
}
void Transform::setLocalScale(const glm::vec3 &scale)
{
    Transform::scale = scale;
    return;
}

void Transform::savePreviousState()
{
    prev_position = position;
    prev_rotation = rotation;
    prev_scale = scale;

    return;
}
