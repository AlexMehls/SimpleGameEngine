#include "playerController.hpp"

#include "userInput.hpp"
#include "coordinateTransform.hpp"
#include "rotationHelpers.hpp"

void PlayerController::loadDefaultValues()
{
    mouseSpeed = defaultValue("mouseSpeed", 0.0005f);
    speed = defaultValue("speed", 5);
    sprintMultiplier = defaultValue("sprint", 4);
}

void PlayerController::update(double deltaTime)
{
    UserInput &input = UserInput::getInstance();
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
    float effectiveSpeed = speed;
    if (input.getAction("sprint"))
    {
        effectiveSpeed *= sprintMultiplier;
    }

    glm::vec2 moveHorizontal = input.getActionDualAxis("move");
    float moveVertical = input.getActionAxis("move_z");
    glm::vec3 moveInput = glm::vec3(moveHorizontal, moveVertical);

    glm::vec3 angles = RotationHelpers::eulerAnglesAlternateWrapping(object->transform.getEulerAngles());
    moveInput = CoordinateTransform::toGamePos(glm::quat(glm::vec3(0, angles.y, 0)) * CoordinateTransform::toOpenGlPos(moveInput));
    glm::normalize(moveInput);
    moveInput *= effectiveSpeed * deltaTime;

    object->transform.move(moveInput);
    return;
}
void PlayerController::fixedUpdate(double deltaTime) {}
