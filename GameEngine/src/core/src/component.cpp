#include "component.hpp"

Component::Component(GameObject *object) : object(object)
{
    assert(object != nullptr);
    object->addComponent(this);
}

Component::~Component() {}
