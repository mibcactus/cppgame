#pragma once
#include "ImageManager.h"
#include "Psymp12Engine.h"
#include "SimpleImage.h"
#include "State.h"

class StateCredits : public State{
public:
    StateCredits() : State() {
        state_name = "CREDITS";
        bg_texture = ImageManager::loadImage("resources/credits.png");
    }
    void drawBG() override;
    void initObjects() override;
    void debugText() override {}

    SimpleImage bg_texture;
    int offset = 0;
};
