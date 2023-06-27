#include "cameraMoveDemo.hpp"

void CameraMoveDemo::loadDefaultValues()
{
    cameraMoveSpeed = defaultValue("speed", 1);
}

void CameraMoveDemo::update(double deltaTime) {}
void CameraMoveDemo::fixedUpdate(double deltaTime)
{
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
