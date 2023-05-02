#pragma once

#include "renderObject.hpp"

class Triangle : public RenderObject
{
public:
    Triangle(GameObject *parent);
};

class Plane : public RenderObject
{
public:
    Plane(GameObject *parent);
};

class Cube : public RenderObject
{
public:
    Cube(GameObject *parent);
};