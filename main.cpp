#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"
#include "mesh.hpp"
#include "behavior.hpp"
#include "testBehaviors.hpp"
#include "debugOutput.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>
#include <filesystem>

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    std::filesystem::path projectFolder = std::filesystem::current_path().parent_path().parent_path();
    std::filesystem::path testAssetPath = projectFolder / "testAssets";

    GameObject &testCube = engine.createGameObject();
    Mesh &testCubeMesh = *(new Mesh(&testCube, engine.defaultAssetFolder().string() + "/testCube3/test_cube.obj"));
    testCubeMesh.loadMesh();
    testCube.transform.setPos(glm::vec3(0, 0, 0));

    GameObject &cubeContainer = engine.createGameObject();
    // Behavior &cubeCBehavior = *(new Behavior(&cubeContainer));
    // cubeCBehavior.setFixedUpdateMethod(spinObject);
    cubeContainer.transform.setPos(glm::vec3(0, 10, 0));
    cubeContainer.transform.setScale(glm::vec3(0.5f));

    GameObject &cubeObject = engine.createGameObject();
    cubeObject.setParent(cubeContainer);
    Mesh &cubeMesh = *(new Mesh(&cubeObject, engine.defaultAssetFolder().string() + "/primitiveObjects/cube/cube.obj"));
    cubeMesh.loadMesh();
    // cubeObject.transform.setLocalPos(glm::vec3(2, 0, 0));
    cubeObject.transform.setPos(glm::vec3(1, 2, 3));
    cubeObject.transform.setScale(glm::vec3(0.5, 0.5, 1));

    DebugOutput::printVec(cubeObject.transform.getPos());

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
    Behavior &cameraBehavior = *(new Behavior(&camera));
    cameraBehavior.setUpdateMethod(cameraMoveDemo);
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    UserInput &input = UserInput::getInstance();

    double prevTime = glfwGetTime();
    double curTime;
    double deltaTime;
    double realFps;
    double gameFps;

    double secAkkum = 0;

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
        }
        */

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