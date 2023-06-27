#include "collisionTest.hpp"

#include "gameEngine.hpp"
#include "debugOutput.hpp"
#include <iostream>

void CollisionTest::loadDefaultValues()
{
}

void CollisionTest::update(double deltaTime) {}
void CollisionTest::fixedUpdate(double deltaTime)
{
    GameEngine &engine = GameEngine::getInstance();

    auto collisions = engine.getCollisions(*object);
    if (collisions.size() > 0 && !colliding)
    {
        colliding = true;
        std::cout << "Collision Entered" << std::endl;
        Collider &other = *collisions[0].otherCollider;
        std::cout << "My id: " << id << ", my object: " << object->id << " Collision with: " << other.id << ", OBJ: " << other.parent()->id << std::endl;
        std::cout << "At: ";
        DebugOutput::printVec(collisions[0].collisionPoint);
    }
    else if (collisions.size() <= 0 && colliding)
    {
        colliding = false;
        std::cout << "Collision Exit" << std::endl;
    }
    return;
}
