#include "spinObject.hpp"

void SpinObject::loadDefaultValues()
{
    speed = defaultValue("speed", 1);
}

void SpinObject::update(double deltaTime) {}
void SpinObject::fixedUpdate(double deltaTime)
{
    object->transform.rotate(glm::vec3(0, speed * deltaTime, 0));
    return;
}
