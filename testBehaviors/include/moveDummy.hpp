#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class MoveDummy : public Behavior
{
public:
    MoveDummy(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "MoveDummy"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    float speed;
};

static BehaviorLookup::MappingSetter mappingSetter("MoveDummy", [](GameObject &object)
                                                   { return new MoveDummy(&object); });
