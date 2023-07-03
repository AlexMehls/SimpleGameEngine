#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class Spawner : public Behavior
{
public:
    Spawner(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "Spawner"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    bool spawned = false;
};

static BehaviorLookup::MappingSetter mappingSetter("Spawner", [](GameObject &object)
                                                   { return new Spawner(&object); });
