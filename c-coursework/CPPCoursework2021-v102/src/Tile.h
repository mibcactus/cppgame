#pragma once
#include "DisplayableObject.h"

class Tile : public DisplayableObject {
    public:
        void virtDraw() override {
            
        }

        
        int tile_ID = 0; //default is not to override
};
