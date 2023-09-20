#include "StateLevel_0.h"

#include "DrawingOutsideWindow.h"
#include "Goober.h"
#include "Player.h"
#include "Psymp12Engine.h"
#include "StatePause.h"

StateLevel_0:: StateLevel_0(){
    state_name = "PATHS";
    levelBG = ImageManager::loadImage("resources/long sky.png");
    stars = ImageManager::loadImage("resources/stars.png");
    level_ID = 0;

    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 27; j++) {
            tilemap[i][j] = new_tilemap[i][j];
        }
    }
    //std::cout << "Level: " << level_ID << " loaded.\n";
}

void StateLevel_0::copyAllBackgroundBuffer() {
    // default
    //levelBG.renderImageApplyingMapping(engine, engine->getBackgroundSurface(), x_offset, 0, levelBG.getWidth(), levelBG.getHeight(), new ImagePixelMappingShiftXY(x_offset, 0));
    //engine->getForegroundSurface()->copyEntireSurface(engine->getBackgroundSurface(
    
    DrawingSurface *fg = engine->getForegroundSurface();
    DrawingSurface *bg = engine->getBackgroundSurface();
    int height = engine->getWindowHeight();

    // scrolls the bg - this just loops it around - need a better method though
    
    //s->copyEntireSurface(b);

    // this just loops everything
    //s->copyRectangleFrom(b, 0, 0, width, height, x_offset, 0); //gets all pixels up to the offset?
    //fg->copyRectangleFrom(bg, 0,0, width, height, x_offset);
    
    
    fg->copyRectangleFrom(bg, 0, 0, levelBG.getWidth(), height, x_offset);
    //fg->copyRectangleFrom(bg, x_offset, 0, width, height, x_offset);
   

    // gets all pixels from outside the screen?
    //fg->copyRectangleFrom(bg, width, 0, width, height, x_offset + width, 0);
    
}

void StateLevel_0::mainLoopBeforeUpdate() {
    if(tilemap_changed == true) {
        tilemap[tilechanged_y][tilechanged_x] = 20; //10,9
        engine->lockBackgroundForDrawing();
        tile_manager.drawGivenTile(engine, 20, tilechanged_location_x, tilechanged_location_y);
        engine->unlockBackgroundForDrawing();
        engine->redrawDisplay();
        tilemap_changed = false;
    }
    
    
}

void StateLevel_0::renderBGimage() {
    //levelBG.renderImageApplyingMapping(engine, engine->getBackgroundSurface(), x_offset, 0, levelBG.getWidth(), levelBG.getHeight(), new ImagePixelMappingShiftXY(x_offset, 0));
    //(engine->getBackgroundSurface(), 0,0,0,0, levelBG.getWidth(), levelBG.getWidth());
    //mapping_bg->drawBackgroundTexture(x_offset);
    //levelBG.renderImage(engine->getBackgroundSurface(), 0, 0, 0,0, 2124, levelBG.getHeight());
/*
    for(int iY = 0; iY < 1024; iY++) {
        for(int iX = 0; iX < 2124; iX++) {
            engine->getBackgroundSurface()->rawSetPixel(iX, iY, levelBG.getPixelColour(iX, iY));
        }
    }*/

    DrawingOutsideWindow::DrawOnSurface(engine->getBackgroundSurface(), this);
    stars.renderImageWithMask(engine->getBackgroundSurface(),0,0,0,0, levelBG.getWidth(), stars.getHeight());
}

void StateLevel_0::renderSubclassBG() {
    int start_y = 0;
    for(int i = 0; i < 13; i++) {
        int start_x = 0;
        for(int j = 0; j < 27; j++) {
            if(tilemap[i][j] != 0) {
                tile_manager.drawGivenTile(engine, tilemap[i][j], start_x, start_y);
            }
            start_x += 80;
        }
        
        start_y += 80;
    }
}

void StateLevel_0::initialiseMobsNormally() {
    mob_count = 5;
    //engine->amount_of_mobs = mob_count;
    //printf("Object count: %d", getObjectCount());
    engine->createObjectArray(getObjectCount());

    Player* player = new Player(this);
    player->setScreenPosition(100, 900);
    engine->storeObjectInArray(0, player);

    Enemy* enemy = new Goober(this, player);
    enemy->setSurfacePosition(1200, 700);
    engine->storeObjectInArray(1, enemy);

    //Goober* goober = new Goober(this, player);
    Goober* enemy1 = new Goober(this, player);
    enemy1->setSurfacePosition(300, 770);
    engine->storeObjectInArray(2, enemy1);

    Goober* enemy2 = new Goober(this, player);
    enemy2->setSurfacePosition(800, 1000);
    engine->storeObjectInArray(3, enemy2);

    Goober* enemy3 = new Goober(this, player);
    enemy3->setSurfacePosition(1800, 200);
    engine->storeObjectInArray(4, enemy3);

    Goober* enemy4 = new Goober(this, player);
    enemy4->setSurfacePosition(1450, 770);
    engine->storeObjectInArray(5, enemy4);
}




