#include "contactLevelLoader.hpp"

#include "gameEngine.hpp"

void ContactLevelLoader::loadDefaultValues()
{
    GameEngine &engine = GameEngine::getInstance();

    std::string level = defaultValue<std::string>("level", "");
    levelPath = engine.levelFolder().string() + "/" + level;
}

void ContactLevelLoader::update(double deltaTime) {}
void ContactLevelLoader::fixedUpdate(double deltaTime)
{
    GameEngine &engine = GameEngine::getInstance();

    auto collisions = engine.getCollisions(*object);
    if (collisions.size() > 0 && !colliding)
    {
        colliding = true;
        engine.loadLevel(levelPath);
    }
    else if (collisions.size() <= 0 && colliding)
    {
        colliding = false;
    }
    return;
}
