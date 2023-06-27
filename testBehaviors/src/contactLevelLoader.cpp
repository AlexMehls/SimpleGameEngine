#include "contactLevelLoader.hpp"

#include "gameEngine.hpp"

void ContactLevelLoader::loadDefaultValues()
{
    std::string level = defaultValue<std::string>("level", "");
    std::filesystem::path projectFolder = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
    levelPath = projectFolder.string() + "/" + level;
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
