#pragma once

#include "component.hpp"

#include <iostream>

class Behavior : public Component
{
public:
    Behavior(GameObject *parent);
    virtual ~Behavior();

    template <typename T>
    T defaultValue(const std::string &valueName, const T &fallback) const
    {
        if (!defaultValues.contains(valueName))
        {
            std::cout << "No value for parameter: " << valueName << ", using fallback value" << std::endl;
            return fallback;
        }
        return defaultValues[valueName];
    }
    virtual void loadDefaultValues();

    virtual std::string type() const override;
    virtual json getLevelParams() const override;
    virtual void loadParams(const json &params) override;

    virtual void update(double deltaTime) override = 0;
    virtual void fixedUpdate(double deltaTime) override = 0;

private:
    json defaultValues;
};
