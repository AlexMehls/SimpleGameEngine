#include "collider.hpp"

#include "gameEngine.hpp"
#include "saveFile.hpp"

Collider::Collider(GameObject *parent) : Component(parent)
{
    GameEngine &engine = GameEngine::getInstance();
    engine.registerCollider(*this);
    transform.setParent(object->transform, true);
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
    SaveFile::addTransform(params, transform);
    return params;
}
void Collider::loadParams(const json &params)
{
    transform = SaveFile::loadTransform(params, &(object->transform));
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