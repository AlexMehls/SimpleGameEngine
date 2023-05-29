#include "cameraController.hpp"

#include "userInput.hpp"
#include "coordinateTransform.hpp"

void CameraController::update(double deltaTime)
{
    UserInput &input = UserInput::getInstance();

    const float mouseSpeed = 0.0005f;
    float speed = 5;
    float sprintMultiplier = 4;

    // Mouse movement
    static float pitch = 0;
    static float yaw = 0;

    glm::vec2 mouseInput = input.getActionDualAxis("look");

    pitch -= mouseSpeed * mouseInput.y;
    if (pitch < -glm::half_pi<float>() || pitch > glm::half_pi<float>())
    {
        yaw += mouseSpeed * mouseInput.x;
    }
    else
    {
        yaw -= mouseSpeed * mouseInput.x;
    }

    object->transform.setLocalEulerAngles(glm::vec3(pitch, yaw, 0));

    // Key movement
    if (input.getAction("sprint"))
    {
        speed *= sprintMultiplier;
    }

    glm::vec2 moveHorizontal = input.getActionDualAxis("move");
    float moveVertical = input.getActionAxis("move_z");
    glm::vec3 moveInput = glm::vec3(moveHorizontal, moveVertical);

    moveInput = CoordinateTransform::toGamePos(object->transform.getRot() * CoordinateTransform::toOpenGlPos(moveInput));
    glm::normalize(moveInput);
    moveInput *= speed * deltaTime;

    object->transform.move(moveInput);
    return;
}
void CameraController::fixedUpdate(double deltaTime) {}
