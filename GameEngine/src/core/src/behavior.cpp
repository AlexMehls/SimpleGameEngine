#include "behavior.hpp"

Behavior::Behavior(GameObject *parent) : Component(parent) {}

void Behavior::setUpdateMethod(const std::function<void(double, GameObject &)> &updateMethod)
{
    Behavior::updateMethod = updateMethod;
    return;
}
void Behavior::setFixedUpdateMethod(const std::function<void(double, GameObject &)> &fixedUpdateMethod)
{
    Behavior::fixedUpdateMethod = fixedUpdateMethod;
    return;
}

std::string Behavior::type() const
{
    return "Behavior";
}

void Behavior::update(double deltaTime)
{
    if (updateMethod != nullptr)
    {
        updateMethod(deltaTime, *object);
    }
    return;
}
void Behavior::fixedUpdate(double deltaTime)
{
    if (fixedUpdateMethod != nullptr)
    {
        fixedUpdateMethod(deltaTime, *object);
    }
    return;
}
