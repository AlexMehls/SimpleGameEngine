#include "renderObject.hpp"

#include <algorithm>
#include <glm/gtc/matrix_transform.hpp>

RenderObject::RenderObject(const GLfloat vertexBufferData[], int vertexBufferSize, const GLfloat colorBufferData[], int colorBufferSize)
{
    m_vertexBufferData = new GLfloat[vertexBufferSize];
    m_vertexBufferSize = vertexBufferSize;
    std::copy(vertexBufferData, vertexBufferData + vertexBufferSize, m_vertexBufferData);

    m_colorBufferData = new GLfloat[colorBufferSize];
    m_colorBufferSize = colorBufferSize;
    std::copy(colorBufferData, colorBufferData + colorBufferSize, m_colorBufferData);

    m_pos = glm::vec3(0);
    updateModelMat();
}

RenderObject::~RenderObject()
{
    delete m_vertexBufferData;
    delete m_colorBufferData;
}

void RenderObject::setPos(const glm::vec3 &pos)
{
    m_pos = pos;
    updateModelMat();
}

const glm::mat4 &RenderObject::getModelMat() const
{
    return m_modelMat;
}

const GLfloat *RenderObject::getVertexBufferData() const
{
    return m_vertexBufferData;
}
int RenderObject::getVertexBufferSize() const
{
    return m_vertexBufferSize;
}
const GLfloat *RenderObject::getColorBufferData() const
{
    return m_colorBufferData;
}
int RenderObject::getColorBufferSize() const
{
    return m_colorBufferSize;
}

void RenderObject::updateModelMat()
{
    m_modelMat = glm::translate(glm::mat4(1.0f), m_pos);
}