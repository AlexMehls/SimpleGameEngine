#include "camera.hpp"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

#include <iostream>

Camera::Camera(GLuint vertexBufferId, GLuint colorBufferId, GLuint mvpMatId)
    : m_vertexBufferId(vertexBufferId), m_colorBufferId(colorBufferId), m_mvpMatId(mvpMatId)
{
    m_pos = glm::vec3(0, 0, 1);
    m_horizontalAngle = 0;
    m_verticalAngle = 0;
    m_fov = 45;
    m_ratio = 4 / (float)3;

    updateViewMat();
    updateProjectionMat();
}

void Camera::setPos(const glm::vec3 &pos)
{
    m_pos = pos;
    updateViewMat();
}

glm::vec3 Camera::getPos() const
{
    return m_pos;
}

void Camera::setRot(float horizontal, float vertical)
{
    m_horizontalAngle = horizontal;
    m_verticalAngle = vertical;

    float hAngle = -m_horizontalAngle + glm::pi<float>();
    float vAngle = -m_verticalAngle;
    m_direction = glm::vec3(
        cos(vAngle) * sin(hAngle),
        sin(vAngle),
        cos(vAngle) * cos(hAngle));

    glm::vec3 right = glm::vec3(
        sin(hAngle - glm::pi<float>() / 2.0f),
        0,
        cos(hAngle - glm::pi<float>() / 2.0f));

    m_up = glm::cross(right, m_direction);

    updateViewMat();
}
void Camera::lookAt(const glm::vec3 &targetPos)
{
    glm::vec3 direction = targetPos - m_pos;
    if (direction == glm::vec3(0))
    {
        return;
    }
    float horizontal = std::atan2(direction.x, -direction.z);
    float vertical = -std::atan2(direction.y, -direction.z);

    setRot(horizontal, vertical);
}
void Camera::setFov(float fov)
{
    m_fov = fov;
    updateProjectionMat();
}
void Camera::setRatio(float ratio)
{
    m_ratio = ratio;
    updateProjectionMat();
}

void Camera::move(const glm::vec3 &deltaPos)
{
    setPos(deltaPos + m_pos);
}
void Camera::rotate(float horizontal, float vertical)
{
    setRot(horizontal + m_horizontalAngle, vertical + m_verticalAngle);
}

void Camera::draw(const RenderObject &toDraw) const
{
    glm::mat4 mvp = m_projectionMat * m_viewMat * toDraw.getModelMat();

    glUniformMatrix4fv(m_mvpMatId, 1, GL_FALSE, &mvp[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getVertexBufferSize(), toDraw.getVertexBufferData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, m_colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getColorBufferSize(), toDraw.getColorBufferData(), GL_STATIC_DRAW);

    int vertices = toDraw.getVertexBufferSize() / sizeof(GLfloat);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void Camera::updateViewMat()
{
    m_viewMat = glm::lookAt(
        m_pos,
        m_pos + m_direction,
        m_up);
}

void Camera::updateProjectionMat()
{
    m_projectionMat = glm::perspective(glm::radians(m_fov), m_ratio, 0.1f, 100.0f);
}