// ReSharper disable CppCStyleCast
#pragma once
#include "ImagePixelMapping.h"


class ImagePixelMappingFlipHorizontally : public ImagePixelMapping {
public:
    bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {
        int width = image.getWidth();
        x = width - x;
        return true;
    }

    bool changePixelColour(int x, int y, int& colour, DrawingSurface* pTarget) override {
        if (colour == m_iTransparencyColour)
            return false; // Don't draw any pixel which should be transparency colour
        return true;
    }

    ImagePixelMappingFlipHorizontally() : ImagePixelMapping(), m_iTransparencyColour(0){}

protected:
    int m_iTransparencyColour;
};







// just do mode 7 or something ;-;
class ImagePixelMappingSkew : public ImagePixelMapping {
public:
    ImagePixelMappingSkew(int width) : ImagePixelMapping() {
        new_width = width;
    }

    bool mapCoordinates(double& x, double& y, const SimpleImage& image) override {
        //int min_offset_x = 0;
        //int max_offset_x = (image.getWidth() - new_width);
        int max_offset_x = new_width;
        int new_x;
        
        //int centre = image.getWidth()/2;

        /*
        if(x > centre) {
            max_offset_x *= -1;
        }*/

        // scale offset by y position
        double y_percent = y / image.getHeight();
        new_x = (int) floor(max_offset_x*y_percent);
        
        // puts the pixel where the offset is
        //x += new_x;
        x += new_x;
        return true;
    }

    bool changePixelColour(int x, int y, int& colour, DrawingSurface* pTarget) override {

        return true;
    }

protected:
    int new_width;
};
