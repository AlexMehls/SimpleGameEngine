#include "spinObject.hpp"

void SpinObject::loadDefaultValues()
{
}

void SpinObject::update(double deltaTime) {}
void SpinObject::fixedUpdate(double deltaTime)
{
    object->transform.rotate(glm::vec3(0, 1 * deltaTime, 0));
    return;
}
