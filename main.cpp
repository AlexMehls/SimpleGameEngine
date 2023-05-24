#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"
#include "mesh.hpp"
#include "behavior.hpp"
#include "testBehaviors.hpp"
#include "debugOutput.hpp"
#include "rotationHelpers.hpp"
#include "inputConfig.hpp"

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

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path testAssetPath = projectFolder / "testAssets";

    std::string testConfigPath = projectFolder.string() + "/testConfig.json";
    // createTestConfig(testConfigPath);

    GameObject &testCube = engine.createGameObject();
    Mesh &testCubeMesh = *(new Mesh(&testCube, engine.defaultAssetFolder().string() + "/testCube3/test_cube.obj"));
    testCubeMesh.loadMesh();
    testCube.transform.setPos(glm::vec3(0, 0, 0));

    GameObject &cubeContainer = engine.createGameObject();
    Behavior &cubeCBehavior = *(new Behavior(&cubeContainer));
    cubeCBehavior.setFixedUpdateMethod(spinObject);
    cubeContainer.transform.setPos(glm::vec3(0, 5, 0));
    cubeContainer.transform.setScale(glm::vec3(0.5f));

    GameObject &cubeObject = engine.createGameObject();
    cubeObject.setParent(cubeContainer);
    Mesh &cubeMesh = *(new Mesh(&cubeObject, engine.defaultAssetFolder().string() + "/primitiveObjects/cube/cube.obj"));
    cubeMesh.loadMesh();
    cubeObject.transform.setLocalPos(glm::vec3(2, 0, 0));
    // cubeObject.transform.setPos(glm::vec3(1, 2, 3));
    cubeObject.transform.setScale(glm::vec3(0.5, 0.5, 1));

    // DebugOutput::printVec(cubeObject.transform.getEulerAngles());
    // DebugOutput::printVec(cubeObject.transform.getPos());

    GameObject &planeObject = engine.createGameObject();
    Mesh &planeMesh = *(new Mesh(&planeObject, engine.defaultAssetFolder().string() + "/primitiveObjects/plane/plane.obj"));
    planeMesh.loadMesh();
    planeObject.transform.setPos(glm::vec3(0, 1, -1.5f));
    planeObject.transform.setScale(glm::vec3(3));

    GameObject &grassObj = engine.createGameObject();
    Mesh &grassMesh = *(new Mesh(&grassObj, testAssetPath.string() + "/GrassPlane/grassPlane.obj"));
    grassMesh.loadMesh();
    grassObj.transform.setPos(glm::vec3(0, 0, -2.0f));

    Camera &camera = engine.createCamera();
    Behavior &cControlB = *(new Behavior(&camera));
    // cameraBehavior.setUpdateMethod(cameraMoveDemo);
    cControlB.setUpdateMethod(cameraMouseControl);
    Behavior &cMoveB = *(new Behavior(&camera));
    cMoveB.setUpdateMethod(cameraKeyMove);
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    Camera &camera2 = engine.createCamera();
    camera2.transform.setPos(glm::vec3(0, 10, 2));
    camera2.transform.lookAt(glm::vec3(0));

    UserInput &input = UserInput::getInstance();
    if (input.loadConfig(testConfigPath))
    {
        std::cout << "Button mapping loaded successfully" << std::endl;
    }

    double prevTime = glfwGetTime();
    double curTime;
    double deltaTime;
    double realFps;
    double gameFps;

    double secAkkum = 0;

    engine.setCursorLock(true);

    while (!glfwWindowShouldClose(engine.window))
    {
        curTime = glfwGetTime();
        deltaTime = curTime - prevTime;
        prevTime = curTime;

        realFps = 1 / deltaTime;

        /*
        secAkkum += deltaTime;
        if (secAkkum > 1)
        {
            secAkkum -= 1;
            std::cout << realFps << std::endl;

            if (engine.activeCamera == &camera)
            {
                engine.activeCamera = &camera2;
            }
            else
            {
                engine.activeCamera = &camera;
            }
        }
        */
        // DebugOutput::printVec(glm::degrees(RotationHelpers::eulerAnglesAlternateWrapping(camera.transform.getEulerAngles())));

        if (deltaTime > (double)1 / 30)
        {
            deltaTime = 1 / 30;
        }
        gameFps = 1 / deltaTime;

        engine.fixedUpdate(deltaTime); // TODO: proper fixedUpdate handling
        engine.update(deltaTime);

        engine.render();

        input.step();
        glfwPollEvents();
    }

    engine.gameEngineTerminate();
    return 0;
}