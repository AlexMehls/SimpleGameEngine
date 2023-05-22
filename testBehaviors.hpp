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

    glm::vec2 mouseInput = input.getDualAxis("mouse");

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

    float speed = 0.1f;
    if (input.getButton("shift"))
    {
        speed *= 2;
    }

    glm::vec3 moveInput = glm::vec3(0);
    moveInput.y += input.getButton("w");
    moveInput.y -= input.getButton("s");
    moveInput.x += input.getButton("d");
    moveInput.x -= input.getButton("a");
    moveInput.z += input.getButton("space");
    moveInput.z -= input.getButton("ctrl");

    moveInput = CoordinateTransform::toGamePos(cameraObject.transform.getRot() * CoordinateTransform::toOpenGlPos(moveInput));
    glm::normalize(moveInput);
    moveInput *= speed;

    cameraObject.transform.move(moveInput);

    return;
}

void spinObject(double deltaTime, GameObject &object)
{
    object.transform.rotate(glm::vec3(0, 1 * deltaTime, 0));
    return;
}
