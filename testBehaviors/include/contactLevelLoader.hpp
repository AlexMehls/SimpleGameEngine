#pragma once

#include "behavior.hpp"
#include "behaviorLookup.hpp"

class ContactLevelLoader : public Behavior
{
public:
    ContactLevelLoader(GameObject *parent) : Behavior(parent) {}

    virtual void loadDefaultValues();
    virtual std::string type() const override { return "ContactLevelLoader"; }

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    std::string levelPath;

    bool colliding = false;
};

static BehaviorLookup::MappingSetter mappingSetter("ContactLevelLoader", [](GameObject &object)
                                                   { return new ContactLevelLoader(&object); });
