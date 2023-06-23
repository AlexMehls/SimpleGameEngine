#pragma once

#include "gameObject.hpp"

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class GameObject;

class Component
{
public:
    const uint64_t id;

    Component(GameObject *object);
    virtual ~Component();

    GameObject *parent();
    virtual std::string type() const = 0;
    virtual json getLevelParams() const = 0;
    virtual void loadParams(const json &params) = 0;

    virtual void saveState();
    virtual void update(double deltaTime) = 0;
    virtual void fixedUpdate(double deltaTime) = 0;

protected:
    GameObject *object;

    friend class GameObject;
};
