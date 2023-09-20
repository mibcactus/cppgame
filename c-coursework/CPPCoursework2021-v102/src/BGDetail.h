#pragma once
#include "Entity.h"

#include "UtilEnums.h"


class BGDetail {
public:
    BGDetail(Psymp12Engine* e, BGDetail_Type type) {
        engine = e;
        switch(type) {
            case BGDetail_Type::TREE:
                texture = ImageManager::loadImage("resources/trees.png");
                break;
            case BGDetail_Type::ROCK:
                texture = ImageManager::loadImage("resources/heart.png");
                break;
            default:
                texture = ImageManager::loadImage("resources/trees.png");
        }
        texture.setTransparencyColour(texture.getPixelColour(0, 0));
    }

    BGDetail(Psymp12Engine* e, SimpleImage t) {
        engine = e;
        texture = t;
    }

    void drawBG() {
        texture.renderImageWithMask(
            engine->getBackgroundSurface(),
            0, 0,
            engine->getWindowWidth(), 0,
            texture.getWidth(), texture.getHeight());
    }

    void drawBG(int start_y) {

        // ReSharper disable once CppCStyleCast
        const int times_to_draw = (int)ceil(engine->getWindowWidth() / texture.getWidth());

        for(int i = 0; i <= times_to_draw; i++) {
            texture.renderImage(
                engine->getBackgroundSurface(),
                0, 0,
                (i * texture.getWidth()), start_y,
                texture.getWidth(), texture.getHeight());
        }
    }

    SimpleImage texture;
    Psymp12Engine* engine;


};
