#include "spawner.hpp"

#include "gameEngine.hpp"
#include "gameObject.hpp"
#include "component.hpp"
#include "factory.hpp"

void Spawner::loadDefaultValues() {}

void Spawner::update(double deltaTime) {}
void Spawner::fixedUpdate(double deltaTime)
{
    if (object->getChildren().size() <= 0 && !spawned)
    {
        spawned = true;

        GameEngine &engine = GameEngine::getInstance();
        GameObject &portal = engine.createGameObject();
        portal.transform.setPos(object->transform.getPos());
        Component *portalMesh = Factory::createComponent("Mesh", portal);
        portalMesh->loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "Portal/sphere.obj"}});
        Factory::createComponent("Collider", portal);
        Component *levelLoader = Factory::createBehavior("ContactLevelLoader", portal);
        levelLoader->loadParams({{"defaultValues", {{"level", "testLevel2.json"}}}});
    }
    return;
}
