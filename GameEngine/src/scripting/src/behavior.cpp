#include "behavior.hpp"

Behavior::Behavior(GameObject *parent) : Component(parent) {}

std::string Behavior::type() const
{
    return "Behavior";
}

json Behavior::getLevelParams() const
{
    json params;
    params["defaultParameters"] = defaultParameters;

    return params;
}

void Behavior::loadParams(const json &params)
{
    defaultParameters = params["defaultParameters"];
    return;
}
