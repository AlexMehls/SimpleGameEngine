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
    glm::vec3 pos;
    float horizontalAngle;
    float verticalAngle;
    glm::vec3 direction;
    glm::vec3 up;
    float fov;
    float ratio;

    GLuint vertexBufferId;
    GLuint colorBufferId;
    GLuint mvpMatId;

    glm::mat4 viewMat;
    glm::mat4 projectionMat;

    void updateViewMat();
    void updateProjectionMat();
};