#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"
#include "mesh.hpp"
#include "debugOutput.hpp"
#include "rotationHelpers.hpp"
#include "inputConfig.hpp"
#include "factory.hpp"

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

    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path testAssetPath = projectFolder / "testAssets";

    GameObject &testCube = engine.createGameObject();
    Mesh &testCubeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", testCube));
    testCubeMesh.loadParams({{"file", engine.defaultAssetFolder().string() + "/testCube3/test_cube.obj"}});
    testCube.transform.setPos(glm::vec3(0, 0, 0));

    GameObject &cubeContainer = engine.createGameObject();
    Factory::createBehavior("SpinObject", cubeContainer);
    cubeContainer.transform.setPos(glm::vec3(0, 5, 0));
    cubeContainer.transform.setScale(glm::vec3(0.5f));

    GameObject &cubeObject = engine.createGameObject();
    cubeObject.setParent(cubeContainer);
    Mesh &cubeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", cubeObject));
    cubeMesh.loadParams({{"file", engine.defaultAssetFolder().string() + "/primitiveObjects/cube/cube.obj"}});
    cubeObject.transform.setLocalPos(glm::vec3(2, 0, 0));
    // cubeObject.transform.setPos(glm::vec3(1, 2, 3));
    cubeObject.transform.setScale(glm::vec3(0.5, 0.5, 1));

    // DebugOutput::printVec(cubeObject.transform.getEulerAngles());
    // DebugOutput::printVec(cubeObject.transform.getPos());

    GameObject &planeObject = engine.createGameObject();
    Mesh &planeMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", planeObject));
    planeMesh.loadParams({{"file", engine.defaultAssetFolder().string() + "/primitiveObjects/plane/plane.obj"}});
    planeObject.transform.setPos(glm::vec3(0, 1, -1.5f));
    planeObject.transform.setScale(glm::vec3(3));

    GameObject &grassObj = engine.createGameObject();
    Mesh &grassMesh = dynamic_cast<Mesh &>(*Factory::createComponent("Mesh", grassObj));
    grassMesh.loadParams({{"file", testAssetPath.string() + "/GrassPlane/grassPlane.obj"}});
    grassObj.transform.setPos(glm::vec3(0, 0, -2.0f));

    Camera &camera = engine.createCamera();
    Factory::createBehavior("CameraController", camera);
    // Factory::createBehavior("CameraMoveDemo", camera);
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    Camera &camera2 = engine.createCamera();
    camera2.transform.setPos(glm::vec3(0, 10, 2));
    camera2.transform.lookAt(glm::vec3(0));

    engine.saveLevel(path);
}

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    // std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path projectFolder = std::filesystem::path(__FILE__).parent_path();
    std::string testConfigPath = projectFolder.string() + "/testConfig.json";
    std::string testLevelPath = projectFolder.string() + "/testLevel.json";

    // createTestConfig(testConfigPath);
    // createTestLevel(testLevelPath);

    UserInput &input = UserInput::getInstance();
    if (input.loadConfig(testConfigPath))
    {
        std::cout << "Button mapping loaded successfully" << std::endl;
    }
    if (engine.loadLevel(testLevelPath))
    {
        std::cout << "Level loaded successfully" << std::endl;
    }
    engine.setCursorLock(true);

    engine.runGameLoop();

    engine.gameEngineTerminate();
    return 0;
}