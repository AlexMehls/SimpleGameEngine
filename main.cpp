#include "primitiveObjects.hpp"
#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"
#include "mesh.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

void cameraMoveDemo(Camera &camera, double deltaTime)
{
    static int cameraMoveDirection = 1;
    const float cameraMoveSpeed = 1;

    camera.transform.move(glm::vec3(deltaTime * cameraMoveSpeed * cameraMoveDirection, 0, 0));
    if (camera.transform.getPos().x >= 5)
    {
        cameraMoveDirection = -1;
    }
    else if (camera.transform.getPos().x <= -5)
    {
        cameraMoveDirection = 1;
    }
    camera.transform.lookAt(glm::vec3(0));
}

void cameraMouseControl(Camera &camera, UserInput &input)
{
    const float mouseSpeed = 0.0005f;

    camera.transform.rotate(glm::vec3(-mouseSpeed * input.mouseDeltaY,
                                      -mouseSpeed * input.mouseDeltaX,
                                      0));
}

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    /*
    GameObject &testCube = engine.createGameObject();
    Mesh testCubeMesh(&testCube, "./TestAssets/testCube2/test_cube.stl");
    testCubeMesh.loadMesh();
    testCube.transform.setPos(glm::vec3(-3, 0, 0));
    */

    GameObject &triangleObject = engine.createGameObject();
    Triangle triangle(&triangleObject);
    triangleObject.transform.setPos(glm::vec3(2, 0, 0));

    GameObject &cubeObject = engine.createGameObject();
    Cube cube(&cubeObject);
    cubeObject.transform.setPos(glm::vec3(0, 1, 0));
    cubeObject.transform.setScale(glm::vec3(0.5, 0.5, 1));

    GameObject &planeObject = engine.createGameObject();
    Plane plane(&planeObject);
    planeObject.transform.setPos(glm::vec3(0, 1, -1.5f));
    planeObject.transform.setScale(glm::vec3(3));

    Camera &camera = engine.createCamera();
    camera.transform.setPos(glm::vec3(0, -5, 2));
    camera.transform.lookAt(glm::vec3(0));

    UserInput &input = UserInput::getInstance();

    double prevTime = glfwGetTime();
    double curTime;
    double deltaTime;
    double realFps;
    double gameFps;

    while (!glfwWindowShouldClose(engine.window))
    {
        curTime = glfwGetTime();
        deltaTime = curTime - prevTime;
        prevTime = curTime;

        realFps = 1 / deltaTime;

        if (deltaTime > (double)1 / 30)
        {
            deltaTime = 1 / 30;
        }

        gameFps = 1 / deltaTime;
        // std::cout << realFps << std::endl;

        cameraMouseControl(camera, input);
        // cameraMoveDemo(camera, deltaTime);

        cubeObject.transform.rotate(glm::vec3(0, 1 * deltaTime, 0));

        engine.fixedUpdate(deltaTime); // TODO: proper fixedUpdate handling
        engine.update(deltaTime);

        engine.render();

        input.step();
        glfwPollEvents();
    }

    engine.gameEngineTerminate();
    return 0;
}