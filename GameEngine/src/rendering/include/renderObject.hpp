#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

class RenderObject
{
public:
    RenderObject(const GLfloat vertexBufferData[], int vertexBufferSize, const GLfloat colorBufferData[], int colorBufferSize);
    ~RenderObject();

    void setPos(const glm::vec3 &pos);
    const glm::mat4 &getModelMat() const;
    const GLfloat *getVertexBufferData() const;
    int getVertexBufferSize() const;
    const GLfloat *getColorBufferData() const;
    int getColorBufferSize() const;

private:
    glm::vec3 m_pos;

    GLfloat *m_vertexBufferData;
    int m_vertexBufferSize;
    GLfloat *m_colorBufferData;
    int m_colorBufferSize;

    glm::mat4 m_modelMat;

    void updateModelMat();
};