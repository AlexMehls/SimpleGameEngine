#pragma once

class UserInput
{
public:
    enum class buttonState
    {
        released,
        pressed,
        held
    };

    double mouseX = 0;
    double mouseDeltaX = 0;
    double mouseY = 0;
    double mouseDeltaY = 0;

    static UserInput &getInstance();
    void step();
};
