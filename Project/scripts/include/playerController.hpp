#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class PlayerController : public Behavior
{
public:
    PlayerController(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "PlayerController"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    float mouseSpeed;
    float speed;
    float sprintMultiplier;

    float pitch = 0;
    float yaw = 0;
};

static BehaviorLookup::MappingSetter mappingSetter("PlayerController", [](GameObject &object)
                                                   { return new PlayerController(&object); });
