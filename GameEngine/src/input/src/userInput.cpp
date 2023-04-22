#include "userInput.hpp"

UserInput &UserInput::getInstance()
{
    static UserInput userInput;
    return userInput;
}

void UserInput::step()
{
    mouseDeltaX = 0;
    mouseDeltaY = 0;
}
