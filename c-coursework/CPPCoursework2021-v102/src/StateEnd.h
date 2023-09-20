#pragma once
#include "ImageManager.h"
#include "SimpleImage.h"
#include "StateLevel.h"

class StateEnd : public State{
public:

    StateEnd() : State() {
        state_name = "END";
    }

    void drawBG() override;
    void initObjects() override;

    SimpleImage bg = ImageManager::loadImage("resources/daysky.png");
    SimpleImage congrats = ImageManager::loadImage("resources/winscreen.png");
};
