#pragma once

#include "transform.hpp"
#include "component.hpp"

#include <list>

class Component;

class GameObject
{
public:
    const uint64_t id;
    Transform transform;

    GameObject(uint64_t id, GameObject *parent);
    ~GameObject();

    GameObject &getParent();
    std::list<GameObject *> &getChildren();

    void setParent(GameObject &parent);

    void update(double deltaTime);
    void fixedUpdate(double deltaTime);

private:
    std::list<Component *> components;

    GameObject *parent;
    std::list<GameObject *> children;
};
