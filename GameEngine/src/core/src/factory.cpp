#include "factory.hpp"

#include "idGenerator.hpp"
#include "behaviorLookup.hpp"
#include "mesh.hpp"
#include "collider.hpp"

namespace Factory
{
    GameObject &createGameObject(GameObject *parent, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects)
    {
        uint64_t id = IdGenerator::getObjectId();
        std::unique_ptr<GameObject> objectPrt = std::make_unique<GameObject>(id, parent);
        GameObject *rawPtr = objectPrt.get();

        gameObjects.insert(std::make_pair(id, std::move(objectPrt)));

        return *rawPtr;
    }
    Camera &createCamera(GameObject *parent, std::map<uint64_t, std::unique_ptr<GameObject>> &gameObjects)
    {
        uint64_t id = IdGenerator::getObjectId();
        Camera *rawPtr = new Camera(id, parent);
        std::unique_ptr<GameObject> objectPtr(rawPtr);

        gameObjects.insert(std::make_pair(id, std::move(objectPtr)));

        return *rawPtr;
    }

    Component *createComponent(const std::string &type, GameObject &object)
    {
        if (type == "Mesh")
        {
            return new Mesh(&object);
        }
        if (type == "Collider")
        {
            return new Collider(&object);
        }
        return createBehavior(type, object);
    }
    Behavior *createBehavior(const std::string &type, GameObject &object)
    {
        return BehaviorLookup::createBehavior(type, object);
    }
} // namespace Factory
