#pragma once

#include "component.hpp"
#include "texture.hpp"
#include "camera.hpp"

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <vector>

struct Vertex
{
    float pos_x;
    float pos_y;
    float pos_z;

    float tex_u;
    float tex_v;

    float normal_x;
    float normal_y;
    float normal_z;

    Vertex() {}

    Vertex(const glm::vec3 &pos, const glm::vec2 &tex, const glm::vec3 &normal)
    {
        pos_x = pos.x;
        pos_y = pos.y;
        pos_z = pos.z;

        tex_u = tex.x;
        tex_v = tex.y;

        normal_x = normal.x;
        normal_y = normal.y;
        normal_z = normal.z;
    }
    Vertex(const glm::vec3 &pos, const glm::vec2 &tex) : Vertex(pos, tex, glm::vec3(0.0f, 0.0f, 0.0f)) {}
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
    virtual json getLevelParams() const override;
    virtual void loadParams(const json &params) override;

    virtual void update(double deltaTime) override;
    virtual void fixedUpdate(double deltaTime) override;

    void render(Camera &camera);

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
