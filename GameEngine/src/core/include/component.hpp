#pragma once

#include "gameObject.hpp"

class GameObject;

class Component
{
public:
    Component() = delete;

    virtual void update(double deltaTime);
    virtual void fixedUpdate(double deltaTime);

private:
    GameObject *object;
};
