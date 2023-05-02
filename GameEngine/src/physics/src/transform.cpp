#include "transform.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include <iostream>

Transform::Transform() : parent(nullptr)
{
    position = glm::vec3(0);
    rotation = glm::quat(1, 0, 0, 0);
    m_scale = glm::vec3(1);

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
        return m_scale;
    }
    return m_scale * parent->getScale();
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
    return m_scale;
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
        m_scale = scale;
    }
    else
    {
        m_scale = scale / parent->getScale();
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
    m_scale = scale;
    return;
}

void Transform::move(const glm::vec3 &deltaPos)
{
    position += deltaPos;
    return;
}
void Transform::rotate(const glm::vec3 &deltaAngles)
{
    rotation = glm::quat(deltaAngles) * rotation;
    return;
}
void Transform::scale(const glm::vec3 &deltaScale)
{
    m_scale += deltaScale;
    return;
}
void Transform::lookAt(const glm::vec3 &targetPos)
{
    setRot(glm::quatLookAt(glm::normalize(targetPos - getPos()), glm::vec3(0, 1, 0)));
    return;
}

void Transform::savePreviousState()
{
    prev_position = getPos();
    prev_rotation = getRot();
    prev_scale = getScale();

    return;
}

glm::mat4 Transform::getModelMat(float interpolation) const
{
    glm::vec3 interpolatedPos = interpolation * getPos() + (1 - interpolation) * prev_position;
    glm::quat interpolatedRot = glm::mix(prev_rotation, getRot(), interpolation);
    glm::vec3 interpolatedScale = interpolation * getScale() + (1 - interpolation) * prev_scale;

    glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), interpolatedPos);
    glm::mat4 rotationMat = glm::mat4_cast(interpolatedRot);
    glm::mat4 scaleMat = glm::scale(interpolatedScale);

    return positionMat * rotationMat * scaleMat; // correct order?
}
