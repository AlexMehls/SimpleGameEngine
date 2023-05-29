#pragma once

#include "gameObject.hpp"

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace SaveFile
{
    // Loads a level form a file into the supplied references
    bool load(const std::string &path, GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects);

    Transform loadTransform(const json &params);

    // Saves the GameObjects into a save file
    bool save(const std::string &path, GameObject &world);

    void addGameObjects(json &level, GameObject &root);
    void addComponents(json &level, const std::list<std::unique_ptr<Component>> &components);
    void addTransform(json &level, const Transform &transform);
} // namespace SaveFile
