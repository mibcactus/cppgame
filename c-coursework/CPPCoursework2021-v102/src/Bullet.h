#pragma once
#include "Entity.h"
#include "StateLevel.h"

#define DISTANCE 400
#define TICKS_PER_SECOND 125

class Bullet : public Entity {
public:
    Bullet(StateLevel* l, int d_x, int d_y, int spawn_x, int spawn_y) : Entity(l) {
        m_iCurrentScreenX = spawn_x - l->x_offset;
        m_iCurrentScreenY = spawn_y - l->y_offset;
        position_x = spawn_x;
        position_y = spawn_y;
        texture = ImageManager::loadImage("resources/bullet.png", true);
        m_iDrawHeight = texture.getHeight();
        m_iDrawWidth = texture.getWidth();

        velocity_y = (velocity_y - speed) * d_y;
        velocity_x = (velocity_x - speed) * d_x;

        level = l;
    }

    StateLevel* level;

    ~Bullet() override {
        printf("Bullet destroyed.\n");
    }

    bool onScreen() {
        if(getScreenX() > getEngine()->getWindowWidth() + 32 || getScreenX() < -32 || getScreenY() > getEngine()->
            getWindowHeight() + 32 || getScreenY() < -32) {
            return false;
        }
        return true;
    }

    void virtDraw() override {
        texture.renderImageWithMask(
            getEngine()->getForegroundSurface(),
            0, 0,
            getScreenX(), getScreenY(),
            texture.getWidth(), texture.getHeight()
        );
    }

    int getLocalXfromSurfaceX(int surface_x) override {
        return surface_x - position_x;
    }

    int getLocalYfromSurfaceY(int surface_y) override {
        return surface_y - position_y;
    }

    void virtDoUpdate(int iCurrentTime) override {
        position_x += velocity_x;
        position_y += velocity_y;

        setScreenPosition(position_x - level->x_offset, position_y + level->y_offset);

        if(!onScreen() || colliding_hitbox || ticks_active == max_ticks) {
            level->bullets.removeDisplayableObject(this);
            delete this;
        }
        ticks_active++;
    }

    int damage = 1;

    int speed = DISTANCE / TICKS_PER_SECOND;

    int velocity_y = 0;
    int velocity_x = 0;

    int ticks_active = 0;
    int max_ticks = 400;
};
