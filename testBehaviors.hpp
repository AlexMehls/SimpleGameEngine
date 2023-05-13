#pragma once

#include "gameObject.hpp"
#include "userInput.hpp"

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

    cameraObject.transform.rotate(glm::vec3(-mouseSpeed * input.mouseDeltaY,
                                            -mouseSpeed * input.mouseDeltaX,
                                            0));
    return;
}

void spinObject(double deltaTime, GameObject &object)
{
    object.transform.rotate(glm::vec3(0, 1 * deltaTime, 0));
    return;
}
