#pragma once
#include "Entity.h"
#include "Player.h"

class Hearts : public Entity {
public:
    Hearts(State *b): Entity(b) {
        texture = ImageManager::loadImage("resources/heart.png", true);
    }

    void virtDraw() override {
        Player *p = dynamic_cast<Player*>(getEngine()->getDisplayableObject(0));
        for(int i = 0; i < p->current_hp; i++) {
                texture.renderImageWithMask(
                getEngine()->getForegroundSurface(),
                0,0,
                (i * texture.getWidth()) + 50, 70,
                texture.getWidth(), texture.getHeight()
                );
        }
    }
};
