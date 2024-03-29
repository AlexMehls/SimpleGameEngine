#pragma once

#include "gameObject.hpp"
#include "idGenerator.hpp"
#include "camera.hpp"
#include "collider.hpp"

#include <map>
#include <unordered_map>
#include <memory>
#include <queue>
#include <filesystem>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/gl.h>

// This class is a singleton
class GameEngine
{
public:
    Camera *activeCamera;
    GLFWwindow *window;

    static GameEngine &getInstance();

    // Loads a level form a file
    bool loadLevel(const std::string &path);
    // Saves the GameObjects into a save file
    bool saveLevel(const std::string &path);

    void setCursorLock(bool locked);
    bool cursorLocked() const;
    void setFullscreen(bool fullscreen);
    bool fullScreen() const;
    void setBackgroundColor(GLfloat red, GLfloat green, GLfloat blue);
    glm::vec3 backgroundColor() const;

    int gameEngineInit();
    void gameEngineTerminate();
    void runGameLoop();

    GameObject &createGameObject();
    Camera &createCamera();
    void addToDestroyQueue(GameObject &toDestroy);
    void clearObjects();

    void registerCollider(Collider &collider);
    void removeCollider(Collider &collider);
    std::vector<Collider::CollisionInfo> getCollisions(GameObject &gameObject) const;
    std::vector<Collider::CollisionInfo> getCollisions(const Collider &collider) const;

    std::filesystem::path defaultAssetFolder() const;
    std::filesystem::path projectAssetFolder() const;
    std::filesystem::path configFolder() const;
    std::filesystem::path levelFolder() const;

    void update(double deltaTime);
    void fixedUpdate(double deltaTime);

    void render(double interpolation);

    GameEngine(GameEngine const &) = delete;
    void operator=(GameEngine const &) = delete;

    GLuint mvpMatrixId;

private:
    GLuint vertexArrayId;
    /*
    GLuint vertexbuffer;
    GLuint colorbuffer;
    */
    GLuint programId;

    bool isInitialized;
    bool m_cursorLocked = false;

    // These are only used to store the values when switching to fullscreen
    int windowPosX = 0;
    int windowPosY = 0;
    int windowSizeX = 0;
    int windowSizeY = 0;

    GameObject world;
    std::map<uint64_t, std::unique_ptr<GameObject>> gameObjects; // switch to unordered_map ?
    std::unordered_map<uint64_t, Collider *> colliders;
    std::unordered_map<uint64_t, std::vector<Collider::CollisionInfo>> collisions;
    std::filesystem::path projectRootPath;

    std::queue<uint64_t> destructionQueue;
    std::string queuedLoadLevel;

    GameEngine();
    ~GameEngine();

    void processCollisions();
    void destroyQueuedObjects();
};
