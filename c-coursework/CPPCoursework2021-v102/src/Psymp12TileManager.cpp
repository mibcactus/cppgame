#include "Psymp12TileManager.h"

#include "ImagePixelMapping.h"

void Psymp12TileManager::virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int mapX, int mapY, int StartX, int StartY) const {
    //grass tile is 5,2 in the sheet - so 400, 160 pixel co-ords on the spritesheet
    
    // 1st two int paras: chooses which tile - uses mapX and mapY to decide which tiles to draw
    // 2nd two paras: where on the map the tile gets drawn
    // 3rd two paras: size of the tile in pixels
    //tilesheet.renderImage(pSurface, 320, 80, StartX, StartY, 80, 80);

    // represent which tile to draw
    mapX *= TILE_SIZE;
    mapY *= TILE_SIZE;

    int surface_x, surface_y, tile_x, tile_y;
    for(int i = 0; i < 80; i++) {
        surface_y = StartY+i;
        tile_y = mapY+i;
        for(int j = 0; j < 80; j++) {
            surface_x = StartX+j;
            tile_x = mapX+j;

            unsigned int pixel_colour = tilesheet.getPixelColour(tile_x, tile_y);
            if(pixel_colour != 0x000000) {
                if(surface_x < pSurface->getSurfaceWidth() && surface_y < pSurface->getSurfaceHeight()) {
                    pSurface->rawSetPixel(surface_x, surface_y, pixel_colour);
                }
            }
            
        }
    }

    
    //tilesheet.renderImage(pSurface, mapX, mapY, StartX, StartY, 80, 80);
}
