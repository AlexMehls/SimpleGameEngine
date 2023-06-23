#include "component.hpp"

#include "idGenerator.hpp"

Component::Component(GameObject *object) : id(IdGenerator::getObjectId()), object(object)
{
    assert(object != nullptr);
    object->addComponent(this);
}

Component::~Component() {}

GameObject *Component::parent()
{
    return object;
}

void Component::saveState() {}
