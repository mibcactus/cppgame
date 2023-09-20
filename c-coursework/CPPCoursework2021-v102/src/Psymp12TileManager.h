#pragma once
#include "BaseEngine.h"
#include "TileManager.h"

#include <utility>

#define TILE_SIZE 80
#define MAX_TILE 18

class Psymp12TileManager : public TileManager {
    public:
        Psymp12TileManager() : TileManager(TILE_SIZE,TILE_SIZE, 16, 13) {
            tilesheet = ImageManager::get()->getImagebyURL("resources/tileset1.png", true, true);
        }

        Psymp12TileManager(std::string ts_url) : TileManager(TILE_SIZE,TILE_SIZE, 16, 13) {
            tilesheet = ImageManager::get()->getImagebyURL(std::move(ts_url), true, true);
        }

        void virtDrawTileAt(BaseEngine* pEngine, DrawingSurface* pSurface, int mapX, int mapY, int StartX,
                            int StartY) const override;

        int findTileI(int i) {
            int tile_i;
            if(i <= 6 ) {
                tile_i = 0;
            } else if (i <= 12) {
                tile_i = 1;
            } else if (i <= 18) {
                tile_i = 2;
            } else {
                tile_i = 3;
            }
            return tile_i;
        }

        int findTileJ(int i, int tile_i) {
            return i - (tile_i*6 +1);
        }
        int findTileJ(int i) {
            return i - (findTileI(i)*6 +1);
        }
    
        void drawGivenTile(BaseEngine* engine, int i, int start_x, int start_y) {

            //printf("drawing tile %d!\n", i);
            //gets the correct pixel co-ords for each tile
            

            int tile_i = findTileI(i);
            int tile_j = findTileJ(i, tile_i);
            //tile_j = i - (tile_i*6 +1);
            
            //printf("tile %d coords are (%d, %d)", i, tile_j, tile_i);
            virtDrawTileAt(engine, engine->getBackgroundSurface(), tile_j, tile_i, start_x, start_y);

        }

    void drawGivenTile(BaseEngine* engine, DrawingSurface *surface, int i, int start_x, int start_y) {

            //printf("drawing tile %d!\n", i);
            //gets the correct pixel co-ords for each tile
            

            int tile_i = findTileI(i);
            int tile_j = findTileJ(i, tile_i);
            //tile_j = i - (tile_i*6 +1);
            
            //printf("tile %d coords are (%d, %d)", i, tile_j, tile_i);
            surface->mySDLLockSurface();
            virtDrawTileAt(engine, surface, tile_j, tile_i, start_x, start_y);
            surface->mySDLUnlockSurface();

        }

        void drawTileOnForeground(BaseEngine* engine, int i, int start_x, int start_y) {
            int tile_i, tile_j = 0;

            //printf("drawing tile %d!\n", i);
            //gets the correct pixel co-ords for each tile

            if(i < 6) {
                tile_i = i - 1;
            }
            else if(i < 12) {
                tile_i = i - 7;
                tile_j = 1;
            }
            else if(i < 18) {
                tile_i = i - 13;
                tile_j = 2;
            }
            else {
                tile_i = 5000;
            }
            //printf("tile %d coords are (%d, %d)", i, tile_j, tile_i);
            // only draws the tile if a valid tile is given!
            if(i != 5000) {
                virtDrawTileAt(engine, engine->getForegroundSurface(), tile_i, tile_j, start_x, start_y);
            }
        }


        // tiles range from 0-18
        // 0 is transparent
        // 1..18 are actual tiles
        // index 7 eg is co-ords 1, 2 on the sheet
        // forumla to find right co-ords:
        /*
         *  x: index given % 6
         *  i < 7: y = i;
         *  i < 13: y = i-6;
         *  i < 19: y = i-12;
         */
        SimpleImage tilesheet;
        //int map[13][16];
        BaseEngine* engine;
};
