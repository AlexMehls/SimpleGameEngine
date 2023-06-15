#include "gameObject.hpp"

#include "gameEngine.hpp"

GameObject::GameObject(uint64_t id, GameObject *parent) : id(id)
{
    if (parent != nullptr)
    {
        setParent(*parent);
    }

    return;
}

GameObject::~GameObject()
{
    return;
}

void GameObject::destroy(bool destroyChildren)
{
    if (destroyChildren)
    {
        for (auto &child : children)
        {
            child->destroy(destroyChildren);
        }
    }
    else
    {
        if (parent != nullptr)
        {
            for (auto &child : children)
            {
                child->setParent(*parent);
            }
        }
        else
        {
            for (auto &child : children)
            {
                child->parent = nullptr;
            }
        }
    }
    if (parent != nullptr)
    {
        parent->removeChild(*this);
    }
    GameEngine::getInstance().addToDestroyQueue(*this);
    return;
}

std::string GameObject::type() const { return "GameObject"; }

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
        parent->removeChild(*this);
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

void GameObject::saveState()
{
    transform.savePreviousState();
    for (auto &component : components)
    {
        component->saveState();
    }
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

void GameObject::removeChild(const GameObject &toRemove)
{
    children.remove_if([&toRemove](auto &child)
                       { return child->id == toRemove.id; });

    return;
}
