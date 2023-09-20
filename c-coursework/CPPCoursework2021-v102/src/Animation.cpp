#include "Animation.h"

void Animation::initialiseFrames(int w) {
    for(int i = current_frame; i < w; i++) {
        Frame new_frame;
        // gets co-ords of each sprite on the sheet
        new_frame.spritesheet_x = i * sprite_width;
        new_frame.spritesheet_y = sprite_height;

        frames.push_back(new_frame);
    }
    for(int i = w; i > 0; i--) {
        Frame new_frame;
        // gets co-ords of each sprite on the sheet
        new_frame.spritesheet_x = i * sprite_width;
        new_frame.spritesheet_y = sprite_height;

        frames.push_back(new_frame);
    }


    /*
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            Frame new_frame;
            // gets co-ords of each sprite on the sheet
            new_frame.spritesheet_x = j*sprite_width;
            new_frame.spritesheet_y = i*sprite_height;

            frames.push_back(new_frame);
        }
    }
    */
}

void Animation::drawCurrentFrameFlipped() {
    Frame cur_frame = getCurrentFrame();
    /*
    int flipped_src_x = cur_frame.spritesheet_x;
    int flipped_src_y = cur_frame.spritesheet_y;

    int target_x = entity->getX();
    int target_y = entity->getY();
    if(cur_frame.flipped) {
        flipped_src_x = cur_frame.spritesheet_x + sprite_width
        target_x = 
    }
    */

    spritesheet.renderImageApplyingMapping(
        entity->getEngine(), entity->getEngine()->getForegroundSurface(),
        entity->getScreenX(), entity->getScreenY(),
        sprite_width, sprite_height, &map);
}


void Animation::drawCurrentFrame() {
    int x_source = getCurrentFrame().spritesheet_x;
    int y_source = getCurrentFrame().spritesheet_y;

    int x_target = entity->getScreenX();
    int y_target = entity->getScreenY();

    // make render with mask and flipping?
    if(flip) {
        drawCurrentFrameFlipped();
    }
    else {
        spritesheet.renderImageWithMask(
            entity->getEngine()->getForegroundSurface(),

            x_source,
            y_source,

            x_target,
            y_target,

            sprite_width,
            sprite_height,
            0x000000
        );
    }
}
