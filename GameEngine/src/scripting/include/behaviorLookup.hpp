#pragma once

#include "gameObject.hpp"
#include "behavior.hpp"

#include <functional>

namespace BehaviorLookup
{
    void setBehaviorCreator(const std::string &name, std::function<Behavior *(GameObject &)> creator);
    Behavior *createBehavior(const std::string &type, GameObject &object);
    struct MappingSetter
    {
        MappingSetter(const std::string &name, std::function<Behavior *(GameObject &)> creator);
    };
} // namespace BehaviorLookup
