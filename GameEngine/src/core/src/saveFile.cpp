#include "saveFile.hpp"

#include "factory.hpp"

#include <fstream>
#include <iostream>

namespace SaveFile
{
    bool load(const std::string &path, GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera)
    {
        std::ifstream f(path);
        json level = json::parse(f);

        clearLevel(world, gameObjects, activeCamera);

        for (auto &gameObject_json : level["gameObjects"])
        {
            loadGameObjects(gameObject_json, world, gameObjects, activeCamera);
        }
        loadComponents(level, world);
        world.transform = loadTransform(level["transform"]);

        return true;
    }

    void clearLevel(GameObject &world, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera)
    {
        std::cout << "clearing level" << std::endl;
        world.getChildren().clear();
        world.getComponents().clear();
        world.transform = Transform();

        gameObjects.clear();

        activeCamera = nullptr;
        std::cout << "cleared level" << std::endl;
        return;
    }

    void loadGameObjects(const json &level, GameObject &root, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects, Camera *&activeCamera)
    {
        GameObject *newObject = nullptr;
        if (level["type"] == "Camera")
        {
            Camera &camera = Factory::createCamera(&root, gameObjects);
            if (level.contains("isActive") && level["isActive"])
            {
                activeCamera = &camera;
            }
            newObject = &camera;
        }
        else
        {
            newObject = &Factory::createGameObject(&root, gameObjects);
        }
        if (level.contains("gameObjects"))
        {
            for (auto &gameObject_json : level["gameObjects"])
            {
                loadGameObjects(gameObject_json, *newObject, gameObjects, activeCamera);
            }
        }
        loadComponents(level, *newObject);
        newObject->transform = loadTransform(level, &(root.transform));

        return;
    }

    void loadComponents(const json &level, GameObject &parent)
    {
        if (!level.contains("components"))
        {
            return;
        }
        for (auto &component_json : level["components"])
        {
            Component *component = Factory::createComponent(component_json["type"], parent);
            if (component_json.contains("parameters"))
            {
                component->loadParams(component_json["parameters"]);
            }
        }
        return;
    }

    Transform loadTransform(const json &params)
    {
        Transform transform;
        if (!params.contains("transform"))
        {
            return transform;
        }
        const json &transformParams = params["transform"];
        if (transformParams.contains("pos"))
        {
            const json &param = transformParams["pos"];
            if (param.is_array() && param.size() == 3)
            {
                transform.setLocalPos(glm::vec3(param[0], param[1], param[2]));
            }
        }
        if (transformParams.contains("rot"))
        {
            const json &param = transformParams["rot"];
            if (param.is_array() && param.size() == 4)
            {
                transform.setLocalRot(glm::quat(param[0], param[1], param[2], param[3]));
            }
        }
        if (transformParams.contains("scale"))
        {
            const json &param = transformParams["scale"];
            if (param.is_array() && param.size() == 3)
            {
                transform.setLocalScale(glm::vec3(param[0], param[1], param[2]));
            }
        }
        return transform;
    }
    Transform loadTransform(const json &params, const Transform *parent)
    {
        Transform transform = loadTransform(params);
        if (parent != nullptr)
        {
            transform.setParent(*parent, true);
        }
        return transform;
    }

    bool save(const std::string &path, GameObject &world, const Camera *activeCamera)
    {
        json level;

        addGameObjects(level, world, activeCamera);

        std::ofstream f(path);
        f << std::setw(4) << level << std::endl;
        return true;
    }

    void addGameObjects(json &level, GameObject &root, const Camera *activeCamera)
    {
        level["type"] = root.type();

        // Special case for active camera
        if (&root == activeCamera)
        {
            level["isActive"] = true;
        }

        for (auto &gameObject : root.getChildren())
        {
            json subtree;
            addGameObjects(subtree, *gameObject, activeCamera);
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