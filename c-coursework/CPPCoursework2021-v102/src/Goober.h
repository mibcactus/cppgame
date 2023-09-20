#pragma once
#include "Enemy.h"

class Goober : public Enemy {
    public:
        Goober(StateLevel *l, Player *p) : Enemy(l, "resources/goober.png", p) {
            type = EnemyType::GOOBER;
            max_hp = 5;
            current_hp = max_hp;
            range = 150;
            //anim = new Animation(this, ImageManager::loadImage("resources/goober sheet.png"), 4, 1);
            spritesheet = ImageManager::loadImage("resources/goobsheet.png");
            anim = new Animation(this, spritesheet,4, 1);
        }
protected:
    SimpleImage spritesheet;
};
