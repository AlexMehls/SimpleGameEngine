#include "transform.hpp"

Transform::Transform()
{
    position = glm::vec3(0);
    rotation = glm::quat(1, 0, 0, 0);
    scale = glm::vec3(0);

    savePreviousState();

    return;
}

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
    // TODO: convert quaternion to angles
    return glm::vec3(0);
}
const glm::vec3 &Transform::getLocalScale() const
{
    return scale;
}

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
    // TODO: convert angles to quat
    return;
}
void Transform::setLocalScale(const glm::vec3 &scale)
{
    Transform::scale = scale;
}

void Transform::savePreviousState()
{
    prev_position = position;
    prev_rotation = rotation;
    prev_scale = scale;

    return;
}
