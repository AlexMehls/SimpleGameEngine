#include "gameObject.hpp"

GameObject::GameObject(uint64_t id, GameObject *parent) : id(id), parent(parent)
{
    // TODO: Change if Transform getts a setter method
    transform.parent = &(parent->transform);
}

GameObject &GameObject::getParent()
{
    return *parent;
}
std::list<GameObject *> &GameObject::getChildren()
{
    return children;
}

void GameObject::setParent(GameObject &newParent)
{
    parent->children.remove_if([this](auto child)
                               { return child->id == this->id; });
    parent = &newParent;
    newParent.children.push_back(this);

    // TODO: Change if Transform getts a setter method
    transform.parent = &(newParent.transform);

    return;
}

void GameObject::update(double deltaTime)
{
    for (auto &component : components)
    {
        component->update(deltaTime);
    }
}
void GameObject::fixedUpdate(double deltaTime)
{
    for (auto &component : components)
    {
        component->fixedUpdate(deltaTime);
    }
}
