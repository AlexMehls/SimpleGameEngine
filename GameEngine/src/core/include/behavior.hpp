#pragma once

#include "component.hpp"
#include <functional>

class Behavior : public Component
{
public:
    Behavior(GameObject *parent);

    void setUpdateMethod(const std::function<void(double, GameObject &)> &updateMethod);
    void setFixedUpdateMethod(const std::function<void(double, GameObject &)> &fixedUpdateMethod);

    virtual std::string type() const override;

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    std::function<void(double, GameObject &)> updateMethod = nullptr;
    std::function<void(double, GameObject &)> fixedUpdateMethod = nullptr;
};
