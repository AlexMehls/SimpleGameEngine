#pragma once

#include "gameObject.hpp"

class GameObject;

class Component
{
public:
    Component(GameObject *object);

    virtual void update(double deltaTime) = 0;
    virtual void fixedUpdate(double deltaTime) = 0;

protected:
    GameObject *object;

    friend class GameObject;
};
