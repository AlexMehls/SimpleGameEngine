#include "saveFile.hpp"

#include <fstream>
#include <iostream>

namespace SaveFile
{
    bool load(const std::string &path, GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects)
    {
        std::ifstream f(path);
        json level = json::parse(f);

        return true;
    }

    Transform loadTransform(const json &params)
    {
        Transform transform;
        if (params.contains("pos"))
        {
            const json &param = params["pos"];
            if (param.is_array() && param.size() == 3)
            {
                transform.setLocalPos(glm::vec3(param[0], param[1], param[2]));
            }
        }
        if (params.contains("rot"))
        {
            const json &param = params["rot"];
            if (param.is_array() && param.size() == 4)
            {
                transform.setLocalRot(glm::quat(param[0], param[1], param[2], param[3]));
            }
        }
        if (params.contains("scale"))
        {
            const json &param = params["scale"];
            if (param.is_array() && param.size() == 3)
            {
                transform.setLocalScale(glm::vec3(param[0], param[1], param[2]));
            }
        }
        return transform;
    }

    bool save(const std::string &path, GameObject &world)
    {
        json level;

        addGameObjects(level, world);

        std::ofstream f(path);
        f << std::setw(4) << level << std::endl;
        return true;
    }

    void addGameObjects(json &level, GameObject &root)
    {
        for (auto &gameObject : root.getChildren())
        {
            json subtree;
            addGameObjects(subtree, *gameObject);
            level["gameObjects"].push_back(std::move(subtree));
        }
        addComponents(level, root.getComponents());
        addTransform(level, root.transform);
    }

    void addComponents(json &level, const std::list<std::unique_ptr<Component>> &components)
    {
        for (auto &component : components)
        {
            json j_comp;
            j_comp["type"] = component->type();
            j_comp["parameters"] = component->getLevelParams();
            level["components"].push_back(std::move(j_comp));
        }
    }

    void addTransform(json &level, const Transform &transform)
    {
        const glm::vec3 &pos = transform.getLocalPos();
        if (pos != glm::vec3(0))
        {
            level["transform"]["pos"] = {pos.x, pos.y, pos.z};
        }

        const glm::quat &rot = transform.getLocalRot();
        if (rot != glm::quat(1, 0, 0, 0))
        {
            level["transform"]["rot"] = {rot.w, rot.x, rot.y, rot.z};
        }

        const glm::vec3 &scale = transform.getLocalScale();
        if (scale != glm::vec3(1))
        {
            level["transform"]["scale"] = {scale.x, scale.y, scale.z};
        }
    }
} // namespace SaveFile
