#include "mesh.hpp"
#include "gameEngine.hpp"

#include <iostream>
#include <filesystem>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

Mesh::MeshEntry::MeshEntry()
{
    VB = GL_INVALID_VALUE;
    IB = GL_INVALID_VALUE;
    NumIndices = 0;
    MaterialIndex = INVALID_MATERIAL;
};

Mesh::MeshEntry::~MeshEntry()
{
    if (VB != GL_INVALID_VALUE)
    {
        glDeleteBuffers(1, &VB);
    }

    if (IB != GL_INVALID_VALUE)
    {
        glDeleteBuffers(1, &IB);
    }
}

void Mesh::MeshEntry::Init(const std::vector<Vertex> &Vertices,
                           const std::vector<unsigned int> &Indices)
{
    NumIndices = Indices.size();

    glGenBuffers(1, &VB);
    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * Vertices.size(), &Vertices[0], GL_STATIC_DRAW);

    glGenBuffers(1, &IB);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NumIndices, &Indices[0], GL_STATIC_DRAW);
}

Mesh::Mesh(GameObject *parent, const std::string &fileName) : Component(parent)
{
    Mesh::fileName = fileName;
    // TODO: Change if Transform getts a setter method
    transform.parent = &(object->transform);
}
Mesh::~Mesh()
{
    clear();
}

void Mesh::clear()
{
    for (unsigned int i = 0; i < textures.size(); i++)
    {
        // SAFE_DELETE(m_Textures[i]);
        delete textures[i];
        textures[i] = nullptr;
    }
}

std::string Mesh::type() const
{
    return "Mesh";
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
    for (int i = 0; i < meshEntries.size(); i++)
    {
        const aiMesh *mesh = scene->mMeshes[i];

        meshEntries[i].MaterialIndex = mesh->mMaterialIndex;
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        const aiVector3D zero3d(0.0f, 0.0f, 0.0f);

        for (unsigned int j = 0; j < mesh->mNumVertices; j++)
        {
            const aiVector3D *pPos = &(mesh->mVertices[j]);
            const aiVector3D *pNormal = mesh->HasNormals() ? &(mesh->mNormals[j]) : &zero3d;
            const aiVector3D *pTexCoord = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][j]) : &zero3d;

            Vertex v(glm::vec3(pPos->x, pPos->y, pPos->z),
                     glm::vec2(pTexCoord->x, pTexCoord->y),
                     glm::vec3(pNormal->x, pNormal->y, pNormal->z));

            vertices.push_back(v);
        }
        for (unsigned int j = 0; j < mesh->mNumFaces; j++)
        {
            const aiFace &Face = mesh->mFaces[j];
            assert(Face.mNumIndices == 3);
            indices.push_back(Face.mIndices[0]);
            indices.push_back(Face.mIndices[1]);
            indices.push_back(Face.mIndices[2]);
        }

        meshEntries[i].Init(vertices, indices);
    }
    // Load textures
    std::string::size_type SlashIndex = fileName.find_last_of("/");
    std::string Dir;

    if (SlashIndex == std::string::npos)
    {
        Dir = ".";
    }
    else if (SlashIndex == 0)
    {
        Dir = "/";
    }
    else
    {
        Dir = fileName.substr(0, SlashIndex);
    }

    bool ret = true;

    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        const aiMaterial *material = scene->mMaterials[i];
        textures[i] = nullptr;

        if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
        {
            aiString path;

            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == aiReturn_SUCCESS)
            {
                std::string fullPath = Dir + "/" + path.data;
                textures[i] = new Texture(GL_TEXTURE_2D, fullPath);

                if (!textures[i]->Load())
                {
                    std::cerr << "Error loading texture " << fullPath << std::endl;
                    delete textures[i];
                    textures[i] = nullptr;
                    ret = false;
                }
                else
                {
                    std::cout << "Loaded texture " << fullPath << std::endl;
                }
            }
        }
        // Load a white texture in case the model does not include its own texture
        if (!textures[i])
        {
            std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
            std::filesystem::path assetFolder = projectFolder / "GameEngine/src/rendering/TestAssets";
            std::filesystem::path defaultTexture = assetFolder / "missing_texture2.png";
            textures[i] = new Texture(GL_TEXTURE_2D, defaultTexture.string());

            ret = textures[i]->Load();
        }
    }
    return ret;
}

void Mesh::render()
{
    GameEngine &engine = GameEngine::getInstance();
    glm::mat4 mvp = engine.activeCamera->getProjViewMat() * transform.getModelMat(1);

    glUniformMatrix4fv(engine.mvpMatrixId, 1, GL_FALSE, &mvp[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    for (unsigned int i = 0; i < meshEntries.size(); i++)
    {
        glBindBuffer(GL_ARRAY_BUFFER, meshEntries[i].VB);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)(3 * sizeof(GLfloat)));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid *)((3 + 2) * sizeof(GLfloat)));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshEntries[i].IB);

        const unsigned int MaterialIndex = meshEntries[i].MaterialIndex;

        if (MaterialIndex < textures.size() && textures[MaterialIndex])
        {
            textures[MaterialIndex]->Bind(GL_TEXTURE0);
        }

        glDrawElements(GL_TRIANGLES, meshEntries[i].NumIndices, GL_UNSIGNED_INT, 0);
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
