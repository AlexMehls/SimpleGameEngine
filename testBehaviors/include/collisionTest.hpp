#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class CollisionTest : public Behavior
{
public:
    CollisionTest(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "CollisionTest"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};

static BehaviorLookup::MappingSetter mappingSetter("CollisionTest", [](GameObject &object)
                                                   { return new CollisionTest(&object); });
