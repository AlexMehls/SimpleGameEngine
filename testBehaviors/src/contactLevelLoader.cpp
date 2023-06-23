#include "contactLevelLoader.hpp"

#include "gameEngine.hpp"

void ContactLevelLoader::update(double deltaTime) {}
void ContactLevelLoader::fixedUpdate(double deltaTime)
{
    std::filesystem::path projectFolder = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
    std::string testLevelPath = projectFolder.string() + "/testLevel.json";

    GameEngine &engine = GameEngine::getInstance();
    static bool colliding = false;

    auto collisions = engine.getCollisions(*object);
    if (collisions.size() > 0 && !colliding)
    {
        colliding = true;
        engine.loadLevel(testLevelPath);
    }
    else if (collisions.size() <= 0 && colliding)
    {
        colliding = false;
    }
    return;
}
