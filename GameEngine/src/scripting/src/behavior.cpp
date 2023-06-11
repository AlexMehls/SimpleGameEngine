#include "behavior.hpp"

Behavior::Behavior(GameObject *parent) : Component(parent) {}
Behavior::~Behavior() {}

std::string Behavior::type() const
{
    return "Behavior";
}

json Behavior::getLevelParams() const
{
    json params;
    params["defaultValues"] = defaultValues;

    return params;
}

void Behavior::loadParams(const json &params)
{
    defaultValues = params["defaultValues"];
    return;
}
