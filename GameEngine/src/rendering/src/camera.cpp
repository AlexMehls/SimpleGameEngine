#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <iostream>

Camera::Camera(GLuint vertexBufferId, GLuint colorBufferId, GLuint mvpMatId)
    : vertexBufferId(vertexBufferId), colorBufferId(colorBufferId), mvpMatId(mvpMatId)
{
    pos = glm::vec3(0, 0, 1);
    horizontalAngle = 0;
    verticalAngle = 0;
    fov = 45;
    ratio = 4 / (float)3;

    updateViewMat();
    updateProjectionMat();
}

void Camera::setPos(const glm::vec3 &newPos)
{
    pos = newPos;
    updateViewMat();
}

glm::vec3 Camera::getPos() const
{
    return pos;
}

void Camera::setRot(float newHorizontal, float newVertical)
{
    horizontalAngle = newHorizontal;
    verticalAngle = newVertical;

    float hAngle = -horizontalAngle + glm::pi<float>();
    float vAngle = -verticalAngle;
    direction = glm::vec3(
        cos(vAngle) * sin(hAngle),
        sin(vAngle),
        cos(vAngle) * cos(hAngle));

    glm::vec3 right = glm::vec3(
        sin(hAngle - glm::pi<float>() / 2.0f),
        0,
        cos(hAngle - glm::pi<float>() / 2.0f));

    up = glm::cross(right, direction);

    updateViewMat();
}
void Camera::lookAt(const glm::vec3 &targetPos)
{
    glm::vec3 direction = targetPos - pos;
    if (direction == glm::vec3(0))
    {
        return;
    }
    float horizontal = std::atan2(direction.x, -direction.z);
    float vertical = -std::atan2(direction.y, -direction.z);

    setRot(horizontal, vertical);
}
void Camera::setFov(float newFov)
{
    fov = newFov;
    updateProjectionMat();
}
void Camera::setRatio(float newRatio)
{
    ratio = newRatio;
    updateProjectionMat();
}

void Camera::move(const glm::vec3 &deltaPos)
{
    setPos(deltaPos + pos);
}
void Camera::rotate(float deltaHorizontal, float deltaVertical)
{
    setRot(deltaHorizontal + horizontalAngle, deltaVertical + verticalAngle);
}

void Camera::draw(const RenderObject &toDraw) const
{
    glm::mat4 mvp = projectionMat * viewMat * toDraw.getModelMat();

    glUniformMatrix4fv(mvpMatId, 1, GL_FALSE, &mvp[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getVertexBufferSize(), toDraw.getVertexBufferData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getColorBufferSize(), toDraw.getColorBufferData(), GL_STATIC_DRAW);

    int vertices = toDraw.getVertexBufferSize() / sizeof(GLfloat);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void Camera::updateViewMat()
{
    viewMat = glm::lookAt(
        pos,
        pos + direction,
        up);
}

void Camera::updateProjectionMat()
{
    projectionMat = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
}