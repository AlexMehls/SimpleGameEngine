#pragma once

#include "renderObject.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera
{
public:
    Camera(GLuint vertexBufferId, GLuint colorBufferId, GLuint mvpMatId);

    void setPos(const glm::vec3 &pos);
    glm::vec3 getPos() const;

    void setRot(float horizontal, float vertical);
    void lookAt(const glm::vec3 &targetPos);
    void setFov(float fov);
    void setRatio(float ratio);

    void move(const glm::vec3 &deltaPos);
    void rotate(float horizontal, float vertical);

    void draw(const RenderObject &toDraw) const;

private:
    glm::vec3 m_pos;
    float m_horizontalAngle;
    float m_verticalAngle;
    glm::vec3 m_direction;
    glm::vec3 m_up;
    float m_fov;
    float m_ratio;

    GLuint m_vertexBufferId;
    GLuint m_colorBufferId;
    GLuint m_mvpMatId;

    glm::mat4 m_viewMat;
    glm::mat4 m_projectionMat;

    void updateViewMat();
    void updateProjectionMat();
};