#include "primitiveObjects.hpp"
#include "camera.hpp"
#include "userInput.hpp"
#include "gameEngine.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <chrono>

int main(int argc, char *argv[])
{
    GameEngine engine = GameEngine::getInstance();

    Triangle triangle;
    triangle.setPos(glm::vec3(2, 0, 0));

    Cube cube;

    Plane plane;
    plane.setPos(glm::vec3(0, -1.5f, 1));

    Camera camera(engine.vertexbuffer, engine.colorbuffer, engine.mvpMatrixId);
    camera.setPos(glm::vec3(0, 2, 5));
    camera.lookAt(glm::vec3(0));
    float speed = 1;
    float mouseSpeed = 0.0005f;

    int cameraMoveDirection = 1;
    float cameraMoveSpeed = 1;

    float ratio;
    int width, height;
    UserInput &input = UserInput::getInstance();

    double prevTime = glfwGetTime();
    double curTime;
    double deltaTime;
    double fps;

    while (!glfwWindowShouldClose(engine.window))
    {
        curTime = glfwGetTime();
        deltaTime = curTime - prevTime;
        prevTime = curTime;

        fps = 1 / deltaTime;
        // std::cout << fps << std::endl;

        glfwGetFramebufferSize(engine.window, &width, &height);
        ratio = width / (float)height;
        // Setting a fixed resolution causes stretching if window shape changes
        camera.setRatio(ratio);

        camera.rotate(mouseSpeed * input.mouseDeltaX,
                      mouseSpeed * input.mouseDeltaY);

        /*
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
        */

        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.draw(cube);
        camera.draw(triangle);
        camera.draw(plane);

        glfwSwapBuffers(engine.window);
        input.step();
        glfwPollEvents();
    }

    return 0;
}