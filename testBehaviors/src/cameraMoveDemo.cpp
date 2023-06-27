#include "cameraMoveDemo.hpp"

void CameraMoveDemo::loadDefaultValues()
{
}

void CameraMoveDemo::update(double deltaTime) {}
void CameraMoveDemo::fixedUpdate(double deltaTime)
{
    static int cameraMoveDirection = 1;
    const float cameraMoveSpeed = 1;

    object->transform.move(glm::vec3(deltaTime * cameraMoveSpeed * cameraMoveDirection, 0, 0));
    if (object->transform.getPos().x >= 5)
    {
        cameraMoveDirection = -1;
    }
    else if (object->transform.getPos().x <= -5)
    {
        cameraMoveDirection = 1;
    }
    object->transform.lookAt(glm::vec3(0));
    return;
}
