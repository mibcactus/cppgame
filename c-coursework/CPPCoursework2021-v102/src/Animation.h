#pragma once
#include <vector>

#include "Entity.h"
#include "Frame.h"
#include "Psymp12ImagePixelMapping.h"
#include "SimpleImage.h"

class Animation {
public:
    std::vector<Frame> frames;
    unsigned int current_frame = 0;
    int sprite_width;
    int sprite_height;
    int ticks_per_frame = 45;
    int last_tick = 0;
    int ticks_since_last_frame = 200;
    bool flip = false;
    SimpleImage spritesheet;

    // give width and height of the spritesheet in terms of tiles
    Animation(Entity* e, SimpleImage s, int width, int height, int start_at = 0) {
        entity = e;
        spritesheet = s;
        sprite_width = spritesheet.getWidth() / width; // pixels/amount of sprites to give pixel size of sprite
        sprite_height = spritesheet.getHeight() / height;
        //spritesheet.setTransparencyColour(0);
        initialiseFrames(width);
        current_frame = start_at;
    }

    ~Animation() {
        //std::cout << "Animation freed.\n";
    }

    void initialiseFrames(int w);

    void drawCurrentFrame();
    void drawCurrentFrameFlipped();

    void updateFrame(int current_time) {
        if(current_time > last_tick + ticks_since_last_frame) {
            goToNextFrame();
            last_tick = current_time;
        }
    }

    void goToNextFrame() {
        // +1 to account for 0-indexing
        if(current_frame + 1 == frames.size()) {
            current_frame = 0;
        }
        else {
            current_frame++;
        }
    }

    Frame getFirstFrame() {
        return frames.front();
    }

    Frame getCurrentFrame() {
        return frames.at(current_frame);
    }

    Frame getLastFrame() {
        return frames.back();
    }


private:
    Entity* entity;
    ImagePixelMappingFlipHorizontally map;
};
