#pragma once

#include "gameObject.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include <glm/glm.hpp>

class Camera : public GameObject
{
public:
    Camera(uint64_t id, GameObject *parent, GLuint vertexBufferId, GLuint colorBufferId, GLuint mvpMatId);
    virtual ~Camera();

    void setFov(float fov);
    void setRatio(float ratio);

    glm::mat4 getProjViewMat();

    virtual void update(double deltaTime);
    virtual void fixedUpdate(double deltaTime);

private:
    float fov;
    float ratio;

    GLuint vertexBufferId;
    GLuint colorBufferId;
    GLuint mvpMatId;

    glm::mat4 viewMat;
    glm::mat4 projectionMat;
    bool projectionMatChanged;

    void updateViewMat();
    void updateProjectionMat();
};