#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class ContactLevelLoader : public Behavior
{
public:
    ContactLevelLoader(GameObject *parent) : Behavior(parent) {}

    virtual std::string type() const override { return "ContactLevelLoader"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;
};

static BehaviorLookup::MappingSetter mappingSetter("ContactLevelLoader", [](GameObject &object)
                                                   { return new ContactLevelLoader(&object); });
