#pragma once

#include "transform.hpp"
#include "component.hpp"

#include <memory>
#include <list>
#include <string>

class Component;

class GameObject
{
public:
    const uint64_t id;
    Transform transform;

    GameObject(uint64_t id, GameObject *parent);
    virtual ~GameObject();

    void destroy(bool destroyChildren = false);

    virtual std::string type() const;
    GameObject &getParent();
    std::list<GameObject *> &getChildren();
    std::list<std::unique_ptr<Component>> &getComponents();

    void setParent(GameObject &parent);

    // Adds component to this object and takes ownership of pointer
    void addComponent(Component *component);

    virtual void update(double deltaTime);
    virtual void fixedUpdate(double deltaTime);

private:
    std::list<std::unique_ptr<Component>> components;

    GameObject *parent = nullptr;
    std::list<GameObject *> children;

    void removeChild(const GameObject &toRemove);
};
