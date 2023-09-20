#pragma once
#include "BulletContainer.h"
#include "Psymp12TileManager.h"
#include "State.h"
#include "StateLevelData.h"

class StateLevel : public State {
public:
    StateLevel() : State() {
        state_name = "LEVEL";
        x_offset = 0;
        y_offset = 0;
        //explosion = ImageManager::loadImage("resources/boom.png");
        button_count++;
    }

    ~StateLevel();

    SimpleImage levelBG;
    void debugText() override;
    void drawBG() override;
    void preDrawFG() override;
    void postDrawFG() override;
    void initObjects() override;
    void onPause() override;

    //void mainLoopBeforeUpdate() override;
    void mainLoopStart() override;
    //void mainLoopPostUpdate() override;
    
    bool fromPause = false;
    StateLevelData data;
    int level_ID = 0;

    // scrolling stuff
    void mainLoopBeforeUpdate() override;
    void copyAllBackgroundBuffer() override;

    //protected:
    bool drawDebugString = false;
    bool tilemap_changed = false;
    int tilechanged_x = 0;
    int tilechanged_y = 0;
    int tilechanged_location_x = 0;
    int tilechanged_location_y = 0;
    std::string bgurl = "resources/starrysky.png";

    int getTile(int x, int y) {
        if(tilemap[y][x])
            return tilemap[y][x];
    }
    
    void transitionToNextStage(StateLevel *next_stage);
    
    virtual void renderSubclassBG();
    virtual void initialiseMobsNormally();
    virtual void initialiseBulletsArray();
    void drawAllTemporaryObjects() override;
    void updateAllTemporaryObjects() override;
    void saveStateData();
    
    void addMenuButton();
    void addHeartsAndMobCounter();
    virtual void addSubclassButtons(){}
    void addForegroundElements();
    
    void addUIbuttons() {
        addSubclassButtons();
        addHeartsAndMobCounter();
        addMenuButton();
    }

    virtual void drawPlayerHitEffect();
    virtual void drawMobHitEffect();
    bool draw_player_hit = false;
    bool draw_mob_hit = false;
    int mob_hit;
    //SimpleImage explosion;
    int time_explosion_drawn;
    
    virtual void allMobsDead();
    
    virtual void renderBGimage();

    virtual void additionalCollisionActions() {}
    
    void checkCollision();

    BulletContainer bullets;
    int timeWhenSpawned = 0;
    int spawnerTile_x = 7;
    int spawnerTile_y = 10;

    // can be used to save bullets if desired
    BulletContainer* getBulletsPtr() {
        return &bullets;
    }

    void flipTile(int x, int y) {
        tilemap[y][x] = 20;
    }

    //int tilemap[3][3]= {{8,8,8}, {11,11,11}, {8,8,8}};
    int tilemap[13][27] =
    {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};
    
        Psymp12TileManager tile_manager = Psymp12TileManager();
        Psymp12TileManager* getTileManagerPtr() {
            return &tile_manager;
        }
        int collision_time = 0;

        // tilemap and entity data?
        // better to just load from a file, esp if i have to do that anyway..
        // or could just subclass this, who knows
        // int tilemap[13][16];
        // std::vector<Entity> mobs;
};
