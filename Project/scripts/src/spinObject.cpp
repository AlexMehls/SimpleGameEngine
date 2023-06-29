#include "spinObject.hpp"

void SpinObject::loadDefaultValues()
{
    speed = defaultValue("speed", 1);
}

void SpinObject::update(double deltaTime) {}
void SpinObject::fixedUpdate(double deltaTime)
{
    rot += speed * deltaTime;
    object->transform.setLocalEulerAngles(glm::vec3(0, rot, 0));
    return;
}
