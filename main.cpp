#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"
#include "mesh.hpp"
#include "debugOutput.hpp"
#include "rotationHelpers.hpp"
#include "inputConfig.hpp"
#include "factory.hpp"
#include "collider.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>
#include <filesystem>

void createTestConfig(const std::string &path)
{
    InputConfig config;
    config.setButton("forward", "w");
    config.setButton("backward", "s");
    config.setButton("left", "a");
    config.setButton("right", "d");
    config.setButton("up", "space");
    config.setButton("down", "ctrl");

    config.setButton("jump", "space");
    config.setButton("sprint", "shift");

    config.setAxis("look_x", "mouse_x");
    config.setAxis("look_y", "mouse_y");

    config.setAxis("move_x", "right", "left");
    config.setAxis("move_y", "forward", "backward");
    config.setAxis("move_z", "up", "down");

    config.setDualAxis("move", "move_x", "move_y");
    config.setDualAxis("look", "mouse");

    config.save(path);

    return;
}

void createTestLevel(const std::string &path)
{
    GameEngine &engine = GameEngine::getInstance();
    engine.clearObjects();

    engine.setBackgroundColor(0.1, 0.1, 0.1);

    GameObject &testCube = engine.createGameObject();
    Mesh &testCubeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", testCube));
    testCubeMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "testCube3/test_cube.obj"}});
    testCube.transform.setPos(glm::vec3(0, 0, 0));

    GameObject &cubeContainer = engine.createGameObject();
    Factory::createBehavior("SpinObject", cubeContainer);
    cubeContainer.transform.setPos(glm::vec3(0, 5, 0));
    cubeContainer.transform.setScale(glm::vec3(0.5f));

    GameObject &cubeObject = engine.createGameObject();
    cubeObject.setParent(cubeContainer);
    Mesh &cubeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", cubeObject));
    cubeMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/cube/cube.obj"}});
    cubeObject.transform.setLocalPos(glm::vec3(2, 0, 0));
    cubeObject.transform.setScale(glm::vec3(0.5, 0.5, 1));

    GameObject &planeObject = engine.createGameObject();
    Mesh &planeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", planeObject));
    planeMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/plane/plane.obj"}});
    planeObject.transform.setPos(glm::vec3(0, 1, -1.5f));
    planeObject.transform.setScale(glm::vec3(3));

    GameObject &grassObj = engine.createGameObject();
    Mesh &grassMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", grassObj));
    grassMesh.loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "GrassPlane/grassPlane.obj"}});
    grassObj.transform.setPos(glm::vec3(0, 0, -2.0f));

    GameObject &portal = engine.createGameObject();
    Mesh &portalMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", portal));
    portalMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    portal.transform.setPos({0, 10, 0});
    Factory::createComponent("Collider", portal);
    Behavior &levelLoader = dynamic_cast<Behavior &>(*Factory::createBehavior("ContactLevelLoader", portal));
    levelLoader.loadParams({{"defaultValues", {{"level", "testLevel2.json"}}}});

    Camera &camera = engine.createCamera();
    Factory::createBehavior("CameraController", camera);
    Collider &cameraCollider = dynamic_cast<Collider &>(*Factory::createComponent("Collider", camera));
    cameraCollider.transform.setScale(glm::vec3(0.1));
    // Factory::createBehavior("CameraMoveDemo", camera);
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    GameObject &rotator = engine.createGameObject();
    Behavior &rotate = dynamic_cast<Behavior &>(*Factory::createBehavior("SpinObject", rotator));
    rotate.loadParams({{"defaultValues", {{"speed", 1}}}});
    Mesh &rotatorMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", rotator));
    rotatorMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    rotatorMesh.transform.setScale(glm::vec3(1.5));
    rotator.transform.setPos({0, 25, 0});

    GameObject &rotator2 = engine.createGameObject();
    rotator2.setParent(rotator);
    Behavior &rotate2 = dynamic_cast<Behavior &>(*Factory::createBehavior("SpinObject", rotator2));
    rotate2.loadParams({{"defaultValues", {{"speed", 2}}}});
    Mesh &rotator2Mesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", rotator2));
    rotator2Mesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    rotator2.transform.setLocalPos(glm::vec3(10, 0, 0));

    GameObject &rotator3 = engine.createGameObject();
    rotator3.setParent(rotator2);
    Mesh &rotator3Mesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", rotator3));
    rotator3Mesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    rotator3Mesh.transform.setScale(glm::vec3(0.5));
    rotator3.transform.setLocalPos(glm::vec3(3, 0, 0));

    engine.saveLevel(path);
}

void createTestLevel2(const std::string &path)
{
    GameEngine &engine = GameEngine::getInstance();
    engine.clearObjects();

    engine.setBackgroundColor(0.3, 0.3, 0.3);

    GameObject &testCube = engine.createGameObject();
    Mesh &testCubeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", testCube));
    testCubeMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "testCube3/test_cube.obj"}});

    GameObject &grassObj = engine.createGameObject();
    Mesh &grassMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", grassObj));
    grassMesh.loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "GrassPlane/grassPlane.obj"}});
    grassObj.transform.setPos(glm::vec3(0, 0, -2.0f));

    GameObject &sphere = engine.createGameObject();
    Mesh &sphereMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", sphere));
    sphereMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    sphere.transform.setPos({3, 0, 0});
    Collider &sphereCollider = dynamic_cast<Collider &>(*Factory::createComponent("Collider", sphere));
    Factory::createBehavior("CollisionTest", sphere);

    GameObject &sphere2 = engine.createGameObject();
    Mesh &sphere2Mesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", sphere2));
    sphere2Mesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    sphere2.transform.setPos({6, 0, 0});
    Collider &sphere2Collider = dynamic_cast<Collider &>(*Factory::createComponent("Collider", sphere2));
    Behavior &moveDummy = dynamic_cast<Behavior &>(*Factory::createBehavior("MoveDummy", sphere2));
    moveDummy.loadParams({{"defaultValues", {{"speed", 2}}}});

    GameObject &portal = engine.createGameObject();
    Mesh &portalMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", portal));
    portalMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    portal.transform.setPos({0, 10, 0});
    Factory::createComponent("Collider", portal);
    Behavior &levelLoader = dynamic_cast<Behavior &>(*Factory::createBehavior("ContactLevelLoader", portal));
    levelLoader.loadParams({{"defaultValues", {{"level", "testLevel.json"}}}});

    GameObject &portal2 = engine.createGameObject();
    Mesh &portal2Mesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", portal2));
    portal2Mesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    portal2.transform.setPos({-10, 0, 0});
    Factory::createComponent("Collider", portal2);
    Behavior &levelLoader2 = dynamic_cast<Behavior &>(*Factory::createBehavior("ContactLevelLoader", portal2));
    levelLoader2.loadParams({{"defaultValues", {{"level", "testLevel3.json"}}}});

    Camera &camera = engine.createCamera();
    Factory::createBehavior("CameraController", camera);
    Collider &cameraCollider = dynamic_cast<Collider &>(*Factory::createComponent("Collider", camera));
    cameraCollider.transform.setScale(glm::vec3(0.1));
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    engine.saveLevel(path);
}

void createDestructibleBall(const glm::vec3 &pos, GameObject &parent)
{
    GameEngine &engine = GameEngine::getInstance();
    GameObject &sphere = engine.createGameObject();
    sphere.setParent(parent);
    Mesh &sphereMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", sphere));
    sphereMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    sphere.transform.setScale(glm::vec3(0.3));
    sphere.transform.setPos(pos);
    Factory::createComponent("Collider", sphere);
    Factory::createBehavior("ContactDestroyer", sphere);
    return;
}

void createTestLevel3(const std::string &path)
{
    GameEngine &engine = GameEngine::getInstance();
    engine.clearObjects();

    engine.setBackgroundColor(0.2, 0.2, 0.2);

    GameObject &planeObject = engine.createGameObject();
    Mesh &planeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", planeObject));
    planeMesh.loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "Water/water.obj"}});
    planeObject.transform.setScale(glm::vec3(1));

    GameObject &monkey = engine.createGameObject();
    Mesh &monkeyMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", monkey));
    monkeyMesh.loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "BlenderMonkey/monkey.obj"}});
    monkey.transform.setPos({10, 0, 3});
    monkey.transform.setEulerAngles({0, -90, 0});

    GameObject &portal = engine.createGameObject();
    Mesh &portalMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", portal));
    portalMesh.loadParams({{"folder", "PROJECT_ASSETS"}, {"file", "Portal/sphere.obj"}});
    portal.transform.setPos({0, 10, 3});
    Factory::createComponent("Collider", portal);
    Behavior &levelLoader = dynamic_cast<Behavior &>(*Factory::createBehavior("ContactLevelLoader", portal));
    levelLoader.loadParams({{"defaultValues", {{"level", "testLevel2.json"}}}});

    GameObject &ballContainer = engine.createGameObject();
    ballContainer.transform.setPos({-15, 0, 3});
    Factory::createBehavior("Spawner", ballContainer);

    createDestructibleBall({-10, -4, 3}, ballContainer);
    createDestructibleBall({-10, -2, 3}, ballContainer);
    createDestructibleBall({-10, 0, 3}, ballContainer);
    createDestructibleBall({-10, 2, 3}, ballContainer);
    createDestructibleBall({-10, 4, 3}, ballContainer);

    createDestructibleBall({-12, -4, 3}, ballContainer);
    createDestructibleBall({-12, -2, 3}, ballContainer);
    createDestructibleBall({-12, 0, 3}, ballContainer);
    createDestructibleBall({-12, 2, 3}, ballContainer);
    createDestructibleBall({-12, 4, 3}, ballContainer);

    GameObject &cameraAnchor = engine.createGameObject();
    Mesh &cameraAnchorMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", cameraAnchor));
    cameraAnchorMesh.loadParams({{"folder", "DEFAULT_ASSETS"}, {"file", "primitiveObjects/sphere/sphere.obj"}});
    cameraAnchor.transform.setPos({0, 0, 3});
    Factory::createComponent("Collider", cameraAnchor);
    // Factory::createBehavior("CameraController", cameraAnchor);
    Factory::createBehavior("PlayerController", cameraAnchor);

    Camera &camera = engine.createCamera();
    camera.setParent(cameraAnchor);
    camera.transform.setLocalPos(glm::vec3(0, -7, 1));

    engine.saveLevel(path);
}

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    std::string testConfigPath = engine.configFolder().string() + "/testConfig.json";
    std::string testLevelPath = engine.levelFolder().string() + "/testLevel.json";
    std::string testLevel2Path = engine.levelFolder().string() + "/testLevel2.json";
    std::string testLevel3Path = engine.levelFolder().string() + "/testLevel3.json";

    // Uncomment to re-build config/level files
    // createTestConfig(testConfigPath);
    // createTestLevel(testLevelPath);
    // createTestLevel2(testLevel2Path);
    // createTestLevel3(testLevel3Path);

    UserInput &input = UserInput::getInstance();
    if (input.loadConfig(testConfigPath))
    {
        std::cout << "Button mapping loaded successfully" << std::endl;
    }
    if (engine.loadLevel(testLevel2Path))
    {
        std::cout << "Level loaded successfully" << std::endl;
    }
    engine.setCursorLock(true);

    engine.runGameLoop();

    engine.gameEngineTerminate();
    return 0;
}