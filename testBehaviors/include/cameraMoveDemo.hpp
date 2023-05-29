#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class CameraMoveDemo : public Behavior
{
public:
    CameraMoveDemo(GameObject *parent) : Behavior(parent) {}

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};

static BehaviorLookup::MappingSetter mappingSetter("CameraMoveDemo", [](GameObject &object)
                                                   { return new CameraMoveDemo(&object); });
