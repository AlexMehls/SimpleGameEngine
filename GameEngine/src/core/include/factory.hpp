#pragma once

#include "gameObject.hpp"
#include "camera.hpp"
#include "component.hpp"
#include "behavior.hpp"

namespace Factory
{
    GameObject &createGameObject(GameObject *parent, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects);
    Camera &createCamera(GameObject *parent, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects);

    Component *createComponent(const std::string &type, GameObject &object);
    Behavior *createBehavior(const std::string &type, GameObject &object);
} // namespace Factory
