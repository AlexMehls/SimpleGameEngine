#include "gameObject.hpp"

GameObject::GameObject(uint64_t id, GameObject *parent) : id(id), parent(parent)
{
    if (parent != nullptr)
    {
        transform.setParent(parent->transform, true);
    }

    return;
}

GameObject::~GameObject()
{
    if (parent == nullptr)
    {
        return;
    }
    for (auto &child : children)
    {
        child->setParent(*parent);
    }

    return;
}

GameObject &GameObject::getParent()
{
    return *parent;
}
std::list<GameObject *> &GameObject::getChildren()
{
    return children;
}
std::list<std::unique_ptr<Component>> &GameObject::getComponents()
{
    return components;
}

void GameObject::setParent(GameObject &newParent)
{
    if (parent != nullptr)
    {
        parent->children.remove_if([this](auto child)
                                   { return child->id == this->id; });
    }

    parent = &newParent;
    newParent.children.push_back(this);

    transform.setParent(newParent.transform);

    return;
}

void GameObject::addComponent(Component *component)
{
    components.emplace_back(component);

    return;
}

void GameObject::update(double deltaTime)
{
    for (auto &component : components)
    {
        component->update(deltaTime);
    }
    return;
}
void GameObject::fixedUpdate(double deltaTime)
{
    for (auto &component : components)
    {
        component->fixedUpdate(deltaTime);
    }
    return;
}
