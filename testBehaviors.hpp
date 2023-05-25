#pragma once

#include "gameObject.hpp"
#include "userInput.hpp"
#include "debugOutput.hpp"
#include "coordinateTransform.hpp"

void cameraMoveDemo(double deltaTime, GameObject &cameraObject)
{
    static int cameraMoveDirection = 1;
    const float cameraMoveSpeed = 1;

    cameraObject.transform.move(glm::vec3(deltaTime * cameraMoveSpeed * cameraMoveDirection, 0, 0));
    if (cameraObject.transform.getPos().x >= 5)
    {
        cameraMoveDirection = -1;
    }
    else if (cameraObject.transform.getPos().x <= -5)
    {
        cameraMoveDirection = 1;
    }
    cameraObject.transform.lookAt(glm::vec3(0));
    return;
}
void cameraMouseControl(double deltaTime, GameObject &cameraObject)
{
    UserInput &input = UserInput::getInstance();

    const float mouseSpeed = 0.0005f;

    static float pitch = 0;
    static float yaw = 0;

    glm::vec2 mouseInput = input.getActionDualAxis("look");

    pitch -= mouseSpeed * mouseInput.y;
    if (pitch < -glm::half_pi<float>() || pitch > glm::half_pi<float>())
    {
        yaw += mouseSpeed * mouseInput.x;
    }
    else
    {
        yaw -= mouseSpeed * mouseInput.x;
    }

    cameraObject.transform.setLocalEulerAngles(glm::vec3(pitch, yaw, 0));
    return;
}
void cameraKeyMove(double deltaTime, GameObject &cameraObject)
{
    UserInput &input = UserInput::getInstance();

    float speed = 5;
    if (input.getAction("sprint"))
    {
        speed *= 4;
    }

    glm::vec2 moveHorizontal = input.getActionDualAxis("move");
    float moveVertical = input.getActionAxis("move_z");
    glm::vec3 moveInput = glm::vec3(moveHorizontal, moveVertical);

    moveInput = CoordinateTransform::toGamePos(cameraObject.transform.getRot() * CoordinateTransform::toOpenGlPos(moveInput));
    glm::normalize(moveInput);
    moveInput *= speed * deltaTime;

    cameraObject.transform.move(moveInput);

    return;
}

void spinObject(double deltaTime, GameObject &object)
{
    object.transform.rotate(glm::vec3(0, 1 * deltaTime, 0));
    return;
}
