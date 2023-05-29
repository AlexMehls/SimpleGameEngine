#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class CameraController : public Behavior
{
public:
    CameraController(GameObject *parent) : Behavior(parent) {}

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};

static BehaviorLookup::MappingSetter mappingSetter("CameraController", [](GameObject &object)
                                                   { return new CameraController(&object); });
