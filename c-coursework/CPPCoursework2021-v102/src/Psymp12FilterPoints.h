#pragma once
#include "DrawingSurface.h"
#include "FilterPoints.h"

class FilterPointScrolling : public FilterPoints {
public:

    //takes in a surface? position to be drawn at a real posiont
    bool filter(DrawingSurface* surface, int& x, int& y, unsigned& uiColour) override {
        //int new_x = x, new_y = y;
        /*
        if(offset_set) {
            // do stuff
        }*/

        //surface->rawSetPixel(new_x, new_y, uiColour);
        return true;
    }





    


    void setOffset(int new_x, int new_y) {
        setXOffset(new_x);
        setYOffset(new_y);
        offset_set = true;
    }
    
    void updateXOffsetWith(int u) {
        x_offset += u;
    }
    
    void setXOffset(int new_offset) {
        x_offset = new_offset;
    }
    void setYOffset(int new_offset) {
        y_offset = new_offset;
    }
    bool offset_set;
    int x_offset = 0;
    int y_offset = 0;


    
};
