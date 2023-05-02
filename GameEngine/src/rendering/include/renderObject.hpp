#pragma once

#include "component.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>

class RenderObject : public Component
{
public:
    Transform transform;

    RenderObject(GameObject *parent, const GLfloat vertexBufferData[], int vertexBufferSize, const GLfloat colorBufferData[], int colorBufferSize);
    ~RenderObject();

    const GLfloat *getVertexBufferData() const;
    int getVertexBufferSize() const;
    const GLfloat *getColorBufferData() const;
    int getColorBufferSize() const;

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

private:
    GLfloat *vertexBufferData;
    int vertexBufferSize;
    GLfloat *colorBufferData;
    int colorBufferSize;
};