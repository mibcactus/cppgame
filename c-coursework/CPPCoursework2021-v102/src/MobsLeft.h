#pragma once
#include "Entity.h"

class MobsLeft : public Entity{
public:
    MobsLeft(State *b) : Entity(b) {
        texture = ImageManager::loadImage("resources/mobs left.png");
    }

    void virtDraw() override {
        texture.renderImageWithMask(getEngine()->getForegroundSurface(),
            0,0, 50, 150, texture.getWidth(), texture.getHeight());
        int num_mobs = state->mob_count;
        //char buf[10];
        //sprintf_s(buf, "%d", num_mobs);
        std::string buf = std::to_string(num_mobs);
        getEngine()->drawForegroundString(75 + texture.getWidth(), 175, buf.c_str(), 0xffff00);
    }
};
