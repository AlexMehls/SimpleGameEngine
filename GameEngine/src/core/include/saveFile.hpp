#pragma once

#include "gameObject.hpp"
#include "camera.hpp"
#include "transform.hpp"

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

namespace SaveFile
{
    // Loads a level form a file into the supplied references
    bool load(const std::string &path, GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera);

    void clearLevel(GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera);
    void loadGameObjects(const json &level, GameObject &root, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera);
    void loadComponents(const json &level, GameObject &parent);
    Transform loadTransform(const json &params);
    Transform loadTransform(const json &params, const Transform *parent);

    // Saves the GameObjects into a save file
    bool save(const std::string &path, GameObject &world, const Camera *activeCamera);

    void addGameObjects(json &level, GameObject &root, const Camera *activeCamera);
    void addComponents(json &level, const std::list<std::unique_ptr<Component>> &components);
    void addTransform(json &level, const Transform &transform);
} // namespace SaveFile
