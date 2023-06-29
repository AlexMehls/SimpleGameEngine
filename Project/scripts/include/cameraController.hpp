#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class CameraController : public Behavior
{
public:
    CameraController(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "CameraController"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    float mouseSpeed;
    float speed;
    float sprintMultiplier;

    float pitch = 0;
    float yaw = 0;
};

static BehaviorLookup::MappingSetter mappingSetter("CameraController", [](GameObject &object)
                                                   { return new CameraController(&object); });
