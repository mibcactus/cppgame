#include "StateLevel_1.h"

#include "DrawingOutsideWindow.h"
#include "Goober.h"
#include "Player.h"
#include "Psymp12Engine.h"

StateLevel_1::StateLevel_1() {
    state_name = "MYSTIC";
    level_ID = 1;
    bgurl = "resources/skyspirals1.PNG";
    levelBG = ImageManager::loadImage(bgurl);
    //stars = ImageManager::loadImage("resources/stars.png");
    x_offset = 0;
    y_offset = 0;

    mob_count = 3;

    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 27; j++) {
            tilemap[i][j] = new_tilemap[i][j];
        }
    }
    //printf("set up tilemap\n");
    //std::cout << "Level: " << level_ID << " loaded.\n";
}

void StateLevel_1::renderBGimage() {
    DrawingOutsideWindow::DrawOnSurface(engine->getBackgroundSurface(), this);
}


void StateLevel_1::copyAllBackgroundBuffer() {
    engine->getForegroundSurface()->copyRectangleFrom(
        engine->getBackgroundSurface(),
        0, 0,
        levelBG.getWidth(),
        engine->getWindowHeight(),
        x_offset);
}

void StateLevel_1::mainLoopBeforeUpdate() {
    if(engine->getModifiedTime() > engine->time_since_surface_changed + 100) {
        engine->current_surface++;
        if(engine->current_surface >= 4) {
            engine->current_surface = 1;
        }
        engine->time_since_surface_changed = engine->getModifiedTime();
    }
    
    if(tilemap_changed == true) {
        tilemap[tilechanged_y][tilechanged_x] = 20; //10,9
        //engine->lockBackgroundForDrawing();
        tile_manager.drawGivenTile(engine, &engine->extra_surface_1, 20, tilechanged_location_x, tilechanged_location_y);
        tile_manager.drawGivenTile(engine, &engine->extra_surface_2, 20, tilechanged_location_x, tilechanged_location_y);
        tile_manager.drawGivenTile(engine, &engine->extra_surface_3, 20, tilechanged_location_x, tilechanged_location_y);
        //engine->unlockBackgroundForDrawing();
        engine->redrawDisplay();
        tilemap_changed = false;
    }
    
}



void StateLevel_1::renderSubclassBG() {
    int start_y = 0;
    for(int i = 0; i < 13; i++) {
        int start_x = 0;
        for(int j = 0; j < 27; j++) {
            tile_manager.drawGivenTile(engine, &engine->extra_surface_1, tilemap[i][j], start_x, start_y);
            tile_manager.drawGivenTile(engine, &engine->extra_surface_2, tilemap[i][j], start_x, start_y);
            tile_manager.drawGivenTile(engine, &engine->extra_surface_3, tilemap[i][j], start_x, start_y);
            start_x += 80;
        }
        start_y += 80;
    }
}

void StateLevel_1::initialiseMobsNormally() {
    mob_count = 4;
    engine->createObjectArray(getObjectCount());
    std::cout << "Object count: " << getObjectCount() << " objects.\n";

    Player *player = new Player(this);
    player->setSurfacePosition(100,900);
    engine->storeObjectInArray(0, player);

    Goober *goober = new Goober(this, player);
    goober->setSurfacePosition(300, 500);
    engine->storeObjectInArray(1, goober);

    Goober *goober2 = new Goober(this, player);
    goober2->setSurfacePosition(700, 900);
    engine->storeObjectInArray(2, goober2);

    Goober *goober3 = new Goober(this, player);
    goober3->setSurfacePosition(1400, 200);
    engine->storeObjectInArray(3, goober3);
    
    Goober *goober4 = new Goober(this, player);
    goober4->setSurfacePosition(1520, 250);
    engine->storeObjectInArray(4, goober4);
}





