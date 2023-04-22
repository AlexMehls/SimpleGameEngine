#include "primitiveObjects.hpp"
#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

void cameraMoveDemo(Camera &camera, double deltaTime)
{
    static int cameraMoveDirection = 1;
    const float cameraMoveSpeed = 1;

    camera.move(glm::vec3(deltaTime * cameraMoveSpeed * cameraMoveDirection, 0, 0));
    if (camera.getPos().x >= 5)
    {
        cameraMoveDirection = -1;
    }
    else if (camera.getPos().x <= -5)
    {
        cameraMoveDirection = 1;
    }
    camera.lookAt(glm::vec3(0));
}

void cameraMouseControl(Camera &camera, UserInput &input)
{
    const float mouseSpeed = 0.0005f;

    camera.rotate(mouseSpeed * input.mouseDeltaX,
                  mouseSpeed * input.mouseDeltaY);
}

int main(int argc, char *argv[])
{
    GameEngine &engine = GameEngine::getInstance();
    engine.gameEngineInit();

    Triangle triangle;
    triangle.setPos(glm::vec3(2, 0, 0));

    Cube cube;

    Plane plane;
    plane.setPos(glm::vec3(0, -1.5f, 1));

    Camera camera(engine.vertexbuffer, engine.colorbuffer, engine.mvpMatrixId);
    camera.setPos(glm::vec3(0, 2, 5));
    camera.lookAt(glm::vec3(0));

    float ratio;
    int width, height;
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

        glfwGetFramebufferSize(engine.window, &width, &height);
        ratio = width / (float)height;

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Setting a fixed resolution causes stretching if window shape changes
        // Updating causes lags and crashes when switching to desktop
        // camera.setRatio(ratio);

        cameraMouseControl(camera, input);
        // cameraMoveDemo(camera, deltaTime);

        camera.draw(cube);
        camera.draw(triangle);
        camera.draw(plane);

        glfwSwapBuffers(engine.window);
        input.step();
        glfwPollEvents();
    }

    engine.gameEngineTerminate();
    return 0;
}