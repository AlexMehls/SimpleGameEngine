#pragma once

#include "gameObject.hpp"

#include <string>

class GameObject;

class Component
{
public:
    Component(GameObject *object);

    virtual std::string type() const = 0;

    virtual void update(double deltaTime) = 0;
    virtual void fixedUpdate(double deltaTime) = 0;

protected:
    GameObject *object;

    friend class GameObject;
};
