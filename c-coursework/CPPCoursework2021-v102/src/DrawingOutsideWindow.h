#pragma once
#include "StateLevel.h"

class DrawingOutsideWindow {
public:
    static void DrawOnSurface(DrawingSurface *surface, const StateLevel *level) {
        for(int iY = 0; iY < 1024; iY++) {
            for(int iX = 0; iX < 2124; iX++) {
                surface->rawSetPixel(iX, iY, level->levelBG.getPixelColour(iX, iY));
            }
        }
    }

    static void DrawOnSurface(DrawingSurface *surface, const SimpleImage& image) {
        for(int iY = 0; iY < 1024; iY++) {
            for(int iX = 0; iX < 2124; iX++) {
                surface->rawSetPixel(iX, iY, image.getPixelColour(iX, iY));
            }
        }
    }

    static void DrawOnSurfaceWithTransparency(DrawingSurface *surface, const SimpleImage *image) {
        for(int iY = 0; iY < 1024; iY++) {
            for(int iX = 0; iX < 2124; iX++) {
                const unsigned int pixel_colour = image->getPixelColour(iX, iY);
                if(pixel_colour != 0x000000) {
                    surface->rawSetPixel(iX, iY, pixel_colour);
                }
            }
        }
    }
};
