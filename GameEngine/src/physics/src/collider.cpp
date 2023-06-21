#include "collider.hpp"

#include "gameEngine.hpp"

Collider::Collider(GameObject *parent) : Component(parent)
{
    GameEngine &engine = GameEngine::getInstance();
    engine.registerCollider(*this);
}
Collider::~Collider()
{
    GameEngine &engine = GameEngine::getInstance();
    engine.removeCollider(*this);
}

std::string Collider::type() const
{
    return "Collider";
}
json Collider::getLevelParams() const
{
    json params;
    return params;
}
void Collider::loadParams(const json &params)
{
    return;
}

void Collider::saveState()
{
    transform.savePreviousState();
}
void Collider::update(double deltaTime)
{
}
void Collider::fixedUpdate(double deltaTime)
{
}