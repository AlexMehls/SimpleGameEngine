#include "contactDestroyer.hpp"

#include "gameEngine.hpp"

void ContactDestroyer::loadDefaultValues() {}
void ContactDestroyer::update(double deltaTime) {}
void ContactDestroyer::fixedUpdate(double deltaTime)
{
    GameEngine &engine = GameEngine::getInstance();

    auto collisions = engine.getCollisions(*object);
    if (collisions.size() > 0 && !colliding)
    {
        colliding = true;
        object->destroy();
    }
    else if (collisions.size() <= 0 && colliding)
    {
        colliding = false;
    }
    return;
}
