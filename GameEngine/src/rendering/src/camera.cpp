#include "camera.hpp"

#include "gameEngine.hpp"

#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

Camera::Camera(uint64_t id, GameObject *parent, GLuint vertexBufferId, GLuint colorBufferId, GLuint mvpMatId)
    : vertexBufferId(vertexBufferId), colorBufferId(colorBufferId), mvpMatId(mvpMatId), GameObject(id, parent)
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
    GameObject::~GameObject();
}

/*
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
*/

void Camera::setFov(float newFov)
{
    fov = newFov;
    projectionMatChanged = true;
}
void Camera::setRatio(float newRatio)
{
    ratio = newRatio;
    projectionMatChanged = true;
}

void Camera::draw(const RenderObject &toDraw)
{
    if (projectionMatChanged)
    {
        updateProjectionMat();
    }
    glm::mat4 mvp = projectionMat * viewMat * toDraw.transform.getModelMat(1);

    glUniformMatrix4fv(mvpMatId, 1, GL_FALSE, &mvp[0][0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getVertexBufferSize(), toDraw.getVertexBufferData(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferId);
    glBufferData(GL_ARRAY_BUFFER, toDraw.getColorBufferSize(), toDraw.getColorBufferData(), GL_STATIC_DRAW);

    int vertices = toDraw.getVertexBufferSize() / sizeof(GLfloat);
    glDrawArrays(GL_TRIANGLES, 0, vertices);
}

void Camera::update(double deltaTime)
{
    GameObject::update(deltaTime);
}
void Camera::fixedUpdate(double deltaTime)
{
    GameObject::fixedUpdate(deltaTime);
    updateViewMat();
}

void Camera::updateViewMat()
{
    // not ideal:
    // glm::vec3 adjustedAngles = transform.getEulerAngles();
    // adjustedAngles.x += glm::pi<double>();
    // adjustedAngles.z -= glm::pi<double>();
    // glm::quat adjustedRot = glm::quat(adjustedAngles);
    viewMat = glm::lookAt(transform.getPos(), transform.getPos() + transform.getRot() * glm::vec3(0, 0, -1), glm::vec3(0, 1, 0));

    // glm::vec3 angles = glm::eulerAngles(glm::quat_cast(viewMat));
    // std::cout << "Correct: Pitch: " << angles.x << ", Yaw: " << angles.y << ", Roll: " << angles.z << std::endl;
    // viewMat = transform.getModelMat(1);
    // angles = glm::eulerAngles(glm::quat_cast(viewMat));
    // std::cout << "Incorrect: Pitch: " << angles.x << ", Yaw: " << angles.y << ", Roll: " << angles.z << std::endl;
}

void Camera::updateProjectionMat()
{
    projectionMat = glm::perspective(glm::radians(fov), ratio, 0.1f, 100.0f);
    projectionMatChanged = false;
}