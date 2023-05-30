#pragma once

#include "component.hpp"

class Behavior : public Component
{
public:
    Behavior(GameObject *parent);
    virtual ~Behavior();

    virtual std::string type() const override;
    virtual json getLevelParams() const override;
    virtual void loadParams(const json &params) override;

    virtual void update(double deltaTime) override = 0;
    virtual void fixedUpdate(double deltaTime) override = 0;

protected:
    json defaultParameters;
};
