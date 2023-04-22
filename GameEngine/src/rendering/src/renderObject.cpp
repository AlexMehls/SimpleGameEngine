#include "renderObject.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject(const GLfloat vertexBufferData[], int vertexBufferSize, const GLfloat colorBufferData[], int colorBufferSize)
{
    RenderObject::vertexBufferData = new GLfloat[vertexBufferSize];
    RenderObject::vertexBufferSize = vertexBufferSize;
    std::copy(vertexBufferData, vertexBufferData + vertexBufferSize, RenderObject::vertexBufferData);

    RenderObject::colorBufferData = new GLfloat[colorBufferSize];
    RenderObject::colorBufferSize = colorBufferSize;
    std::copy(colorBufferData, colorBufferData + colorBufferSize, RenderObject::colorBufferData);

    pos = glm::vec3(0);
    updateModelMat();
}

RenderObject::~RenderObject()
{
    delete vertexBufferData;
    delete colorBufferData;
}

void RenderObject::setPos(const glm::vec3 &newPos)
{
    pos = newPos;
    updateModelMat();
}

const glm::mat4 &RenderObject::getModelMat() const
{
    return modelMat;
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

void RenderObject::updateModelMat()
{
    modelMat = glm::translate(glm::mat4(1.0f), pos);
}