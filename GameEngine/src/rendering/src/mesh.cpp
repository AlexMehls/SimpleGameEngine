#include "mesh.hpp"

#include "gameEngine.hpp"
#include "saveFile.hpp"

#include <iostream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Mesh::MeshEntry::MeshEntry()
{
    vertexBuffer = GL_INVALID_VALUE;
    indexBuffer = GL_INVALID_VALUE;
    nIndices = 0;
    materialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
    if (vertexBuffer != GL_INVALID_VALUE)
    {
        glDeleteBuffers(1, &vertexBuffer);
    }

    if (indexBuffer != GL_INVALID_VALUE)
    {
        glDeleteBuffers(1, &indexBuffer);
    }
}

void Mesh::MeshEntry::init(const std::vector<Vertex> &vertices,
                           const std::vector<unsigned int> &indices)
{
    nIndices = indices.size();

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * nIndices, &indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh(GameObject *parent) : Component(parent)
{
    transform.setParent(object->transform, true);
}
Mesh::Mesh(GameObject *parent, const std::string &fileName) : Component(parent)
{
    Mesh::fileName = fileName;
    transform.setParent(object->transform, true);

    loadMesh();
}
Mesh::~Mesh()
{
    clear();
}

void Mesh::clear()
{
    for (unsigned int i = 0; i < textures.size(); ++i)
    {
        delete textures[i];
        textures[i] = nullptr;
    }
}

std::string Mesh::type() const
{
    return "Mesh";
}

json Mesh::getLevelParams() const
{
    json params;
    params["file"] = fileName;
    SaveFile::addTransform(params, transform);

    return params;
}

void Mesh::loadParams(const json &params)
{
    fileName = params["file"];
    transform = SaveFile::loadTransform(params, &(object->transform));

    loadMesh();
    return;
}

void Mesh::update(double deltaTime) {}
void Mesh::fixedUpdate(double deltaTime) {}

bool Mesh::loadMesh()
{
    clear();

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(fileName,
                                             aiProcess_CalcTangentSpace |
                                                 aiProcess_Triangulate |
                                                 aiProcess_JoinIdenticalVertices |
                                                 aiProcess_SortByPType);
    if (scene == nullptr)
    {
        std::cerr << "Couldn't open scene file " << fileName << std::endl;
        return false;
    }
    meshEntries.resize(scene->mNumMeshes);
    textures.resize(scene->mNumMaterials);

    loadMeshes(scene);
    return loadTextures(scene);
}

void Mesh::render(Camera &camera)
{
    glm::mat4 mvp = camera.getProjViewMat() * transform.getModelMat(1);

    GameEngine &engine = GameEngine::getInstance();
    glUniformMatrix4fv(engine.mvpMatrixId, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < meshEntries.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, meshEntries[i].vertexBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)((3 + 2) * sizeof(GLfloat)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEntries[i].indexBuffer);

        const unsigned int MaterialIndex = meshEntries[i].materialIndex;

        if (MaterialIndex < textures.size() && textures[MaterialIndex])
        {
            textures[MaterialIndex]->bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, meshEntries[i].nIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    return;
}

void Mesh::loadMeshes(const aiScene *scene)
{
    std::cout << "Found " << meshEntries.size() << " sub-mesh(es)" << std::endl;
    for (int i = 0; i < meshEntries.size(); ++i)
    {
        const aiMesh *mesh = scene->mMeshes[i];

        meshEntries[i].materialIndex = mesh->mMaterialIndex;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        const aiVector3D zero3d(0.0f, 0.0f, 0.0f);

        for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
        {
            const aiVector3D *pPos = &(mesh->mVertices[j]);
            const aiVector3D *pNormal = mesh->HasNormals() ? &(mesh->mNormals[j]) : &zero3d;
            const aiVector3D *pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &zero3d;

            Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
                     glm::vec2(pTexCoord->x, pTexCoord->y),
                     glm::vec3(pNormal->x, pNormal->y, pNormal->z));

            vertices.push_back(v);
        }
        for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
        {
            const aiFace &face = mesh->mFaces[j];
            assert(face.mNumIndices == 3);
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        meshEntries[i].init(vertices, indices);
    }
    return;
}

bool Mesh::loadTextures(const aiScene *scene)
{
    std::string directory = std::filesystem::path(fileName).remove_filename().string();

    bool ret = true;
    for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
    {
        const aiMaterial *material = scene->mMaterials[i];
        textures[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;

            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == aiReturn_SUCCESS)
            {
                std::string fullPath = directory + path.data;
                textures[i] = new Texture(GL_TEXTURE_2D, fullPath);

                if (!textures[i]->load())
                {
                    std::cerr << "Error loading texture " << fullPath << std::endl;
                    delete textures[i];
                    textures[i] = nullptr;

                    // Load "missing texture" texture in place off failed texture
                    std::filesystem::path defaultTexture = GameEngine::getInstance().defaultAssetFolder() / "missing_texture2.png";
                    textures[i] = new Texture(GL_TEXTURE_2D, defaultTexture.string());

                    ret = textures[i]->load();
                }
                else
                {
                    std::cout << "Loaded texture " << fullPath << std::endl;
                }
            }
            else
            {
                // Load "missing texture" texture in place off failed texture
                std::filesystem::path defaultTexture = GameEngine::getInstance().defaultAssetFolder() / "missing_texture2.png";
                textures[i] = new Texture(GL_TEXTURE_2D, defaultTexture.string());

                ret = textures[i]->load();
            }
        }
        // Load a white texture in case the model does not include its own texture
        if (!textures[i])
        {
            std::filesystem::path defaultTexture = GameEngine::getInstance().defaultAssetFolder() / "default_texture.png";
            textures[i] = new Texture(GL_TEXTURE_2D, defaultTexture.string());

            ret = textures[i]->load();
        }
    }
    return ret;
}
