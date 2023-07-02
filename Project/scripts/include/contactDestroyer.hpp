#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class ContactDestroyer : public Behavior
{
public:
    ContactDestroyer(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "ContactDestroyer"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    bool colliding = false;
};

static BehaviorLookup::MappingSetter mappingSetter("ContactDestroyer", [](GameObject &object)
                                                   { return new ContactDestroyer(&object); });
