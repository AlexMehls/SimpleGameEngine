#include "renderObject.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject(GameObject *parent, const GLfloat vertexBufferData[], int vertexBufferSize, const GLfloat colorBufferData[], int colorBufferSize) : Component(parent)
{
    // TODO: Change if Transform getts a setter method
    transform.parent = &(object->transform);

    RenderObject::vertexBufferData = new GLfloat[vertexBufferSize];
    RenderObject::vertexBufferSize = vertexBufferSize;
    std::copy(vertexBufferData, vertexBufferData + vertexBufferSize, RenderObject::vertexBufferData);

    RenderObject::colorBufferData = new GLfloat[colorBufferSize];
    RenderObject::colorBufferSize = colorBufferSize;
    std::copy(colorBufferData, colorBufferData + colorBufferSize, RenderObject::colorBufferData);
}

RenderObject::~RenderObject()
{
    delete vertexBufferData;
    delete colorBufferData;
}

const GLfloat *RenderObject::getVertexBufferData() const
{
    return vertexBufferData;
}
int RenderObject::getVertexBufferSize() const
{
    return vertexBufferSize;
}
const GLfloat *RenderObject::getColorBufferData() const
{
    return colorBufferData;
}
int RenderObject::getColorBufferSize() const
{
    return colorBufferSize;
}

std::string RenderObject::type() const
{
    return "RenderObject";
}

void RenderObject::update(double deltaTime) {}
void RenderObject::fixedUpdate(double deltaTime) {}