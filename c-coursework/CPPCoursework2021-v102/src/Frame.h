#pragma once

// used for animations
struct Frame {
    // finds the frame on the spritesheet
    int spritesheet_x = 0;
    int spritesheet_y = 0;
    
    // tells animation manager whether or not to flip the frame
    // by default flipping is assumed to be horizontal, vertical flipping is there just in case
    bool flipped = false;
    bool flipped_y = false;

    // used to set the speed of the animation
    int ticks = 45;
};
