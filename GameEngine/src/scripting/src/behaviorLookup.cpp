#include "behaviorLookup.hpp"

#include <unordered_map>
#include <iostream>

namespace BehaviorLookup
{
    static std::unordered_map<std::string, std::function<Behavior *(GameObject &)>> behaviorCreators;
    void setBehaviorCreator(const std::string &name, std::function<Behavior *(GameObject &)> creator)
    {
        behaviorCreators[name] = creator;
    }
    Behavior *createBehavior(const std::string &type, GameObject &object)
    {
        if (behaviorCreators.contains(type))
        {
            return behaviorCreators[type](object);
        }
        std::cerr << "Missing behavior creator for type: " << type << std::endl;
        return nullptr;
    }
    MappingSetter::MappingSetter(const std::string &name, std::function<Behavior *(GameObject &)> creator)
    {
        setBehaviorCreator(name, creator);
    }

} // namespace BehaviorLookup
