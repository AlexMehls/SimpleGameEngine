#pragma once

#include "component.hpp"
#include "texture.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    glm::vec3 m_pos;
    glm::vec2 m_tex;
    glm::vec3 m_normal;

    Vertex() {}

    Vertex(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &normal)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = normal;
    }

    Vertex(const glm::vec3 &pos, const glm::vec2 &tex)
    {
        m_pos = pos;
        m_tex = tex;
        m_normal = glm::vec3(0.0f, 0.0f, 0.0f);
    }
};

class Mesh : public Component
{
public:
    Transform transform;

    Mesh(GameObject *parent, const std::string &fileName);
    ~Mesh();

    void clear();
    bool loadMesh();

    virtual std::string type() const override;

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

    void render();

private:
#define INVALID_MATERIAL 0xFFFFFFFF
    struct MeshEntry
    {
        MeshEntry();
        ~MeshEntry();

        void Init(const std::vector<Vertex> &Vertices,
                  const std::vector<unsigned int> &Indices);

        GLuint VB;
        GLuint IB;
        unsigned int NumIndices;
        unsigned int MaterialIndex;
    };

    std::string fileName;

    std::vector<MeshEntry> meshEntries;
    std::vector<Texture *> textures;
};
