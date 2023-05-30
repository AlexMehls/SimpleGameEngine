#include "camera.hpp"

#include "gameEngine.hpp"
#include "coordinateTransform.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera(uint64_t id, GameObject *parent)
    : GameObject(id, parent)
{
    fov = 45;
    ratio = 4 / (float)3;
    projectionMatChanged = true;
}
Camera::~Camera()
{
    GameEngine &engine = GameEngine::getInstance();
    if (engine.activeCamera == this)
    {
        engine.activeCamera = nullptr;
    }
}

std::string Camera::type() const { return "Camera"; }

void Camera::setFov(float newFov)
{
    if (newFov != fov)
    {
        fov = newFov;
        projectionMatChanged = true;
    }
    return;
}
void Camera::setRatio(float newRatio)
{
    if (newRatio != ratio && newRatio >= 0.01 && newRatio <= 100)
    {
        ratio = newRatio;
        projectionMatChanged = true;
    }
    return;
}

/*
void Camera::draw(const RenderObject &toDraw)
{
    glm::mat4 mvp = getProjViewMat() * toDraw.transform.getModelMat(1);

    glUniformMatrix4fv(mvpMatId, 1, GL_FALSE, &mvp[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getVertexBufferSize(), toDraw.getVertexBufferData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getColorBufferSize(), toDraw.getColorBufferData(), GL_STATIC_DRAW);

    int vertices = toDraw.getVertexBufferSize() / sizeof(GLfloat);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}
*/

glm::mat4 Camera::getProjViewMat()
{
    if (projectionMatChanged)
    {
        updateProjectionMat();
    }
    return projectionMat * viewMat;
}

void Camera::update(double deltaTime)
{
    GameObject::update(deltaTime);
    updateViewMat();
}
void Camera::fixedUpdate(double deltaTime)
{
    GameObject::fixedUpdate(deltaTime);
    updateViewMat();
}

void Camera::updateViewMat()
{
    // transform coordinates to OpenGl coordinates
    glm::vec3 cameraPos = CoordinateTransform::toOpenGlPos(transform.getPos());
    glm::quat cameraRot = transform.getRot();
    viewMat = glm::lookAt(cameraPos, cameraPos + cameraRot * glm::vec3(0, 0, -1), cameraRot * glm::vec3(0, 1, 0));
}

void Camera::updateProjectionMat()
{
    projectionMat = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
    projectionMatChanged = false;
}