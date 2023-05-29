#include "spinObject.hpp"

void SpinObject::update(double deltaTime)
{
    object->transform.rotate(glm::vec3(0, 1 * deltaTime, 0));
    return;
}

void SpinObject::fixedUpdate(double deltaTime) {}
