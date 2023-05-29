#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class SpinObject : public Behavior
{
public:
    SpinObject(GameObject *parent) : Behavior(parent) {}

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};

static BehaviorLookup::MappingSetter mappingSetter("SpinObject", [](GameObject &object)
                                                   { return new SpinObject(&object); });
