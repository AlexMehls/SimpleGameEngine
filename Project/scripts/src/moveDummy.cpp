#include "moveDummy.hpp"

#include "userInput.hpp"

void MoveDummy::loadDefaultValues()
{
    speed = defaultValue("speed", 1);
}

void MoveDummy::update(double deltaTime) {}
void MoveDummy::fixedUpdate(double deltaTime)
{
    UserInput &input = UserInput::getInstance();
    float dx = (int)input.getButton("k") - (int)input.getButton("h");
    float dy = (int)input.getButton("u") - (int)input.getButton("j");
    dx *= speed * deltaTime;
    dy *= speed * deltaTime;

    object->transform.move({dx, dy, 0});
    return;
}
