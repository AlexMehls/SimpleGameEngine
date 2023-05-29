#pragma once

#include "gameObject.hpp"

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameObject;

class Component
{
public:
    Component(GameObject *object);

    virtual std::string type() const = 0;
    virtual json getLevelParams() const = 0;
    virtual void loadParams(const json &params) = 0;

    virtual void update(double deltaTime) = 0;
    virtual void fixedUpdate(double deltaTime) = 0;

protected:
    GameObject *object;

    friend class GameObject;
};
