#pragma once

#ifndef PSYMP12ENGINE_H
#define PSYMP12ENGINE_H

#include "State.h"
#include "Psymp12TileManager.h"

class Psymp12Engine : public BaseEngine {
    public:

        Psymp12Engine();
    
        ~Psymp12Engine() {
            if (game_state) {
                delete game_state;
            }
            destroyOldObjects(true);
            ImageManager::destroyImageManager();

        }

        void transitionTo(State *new_state) {
            if(game_state) {
                delete game_state;
            }
            game_state = new_state;
            game_state->setEngine(this);
        }

        void drawStateBG() {
            game_state->drawBG();
        }
    
        void virtSetupBackgroundBuffer() override;
        int virtInitialiseObjects() override;
        int virtInitialise() override;

        //void virtMainLoopPreUpdate() override;
        void virtMainLoopPostUpdate() override;
        void virtMainLoopDoBeforeUpdate() override;
        void virtMainLoopDoAfterUpdate() override;
    
        void virtMainLoopStartIteration() override;
        void virtPreDraw() override;
        void virtPostDraw() override;
    
        void virtKeyDown(int iKeyCode) override;
    
        // void virtDrawStringsUnderneath() override; // implement later
        void virtDrawStringsOnTop() override;
        void virtCleanUp() override;
    
        void drawAllObjects() override;
    
        void createCorners(int x, int y, int colour);
        void drawGrid(int x, int y);
        void drawDebugText();

        void copyAllBackgroundBuffer() override;
        void defaultCreateSurfaces() {
            BaseEngine::virtCreateSurfaces();
        }
        void virtCreateSurfaces() override;

        DrawingSurface getTHEforeground() {
            return m_oTheForegroundSurface;
        }

        DrawingSurface getTHEbackground() {
            return m_oTheBackgroundSurface;
        }

        void changeSurface(DrawingSurface newbg) {
            *m_pBackgroundSurface = newbg;
        }
    
        void defaultCopyAllBackgroundBuffer() {
            m_pForegroundSurface->copyEntireSurface(m_pBackgroundSurface);
        }

        int getMobCount() {
            return game_state->mob_count;
        }
        int getFGCount() {
            return game_state->fg_count;
        }

        int getFullCount() {
            return game_state->mob_count + game_state->fg_count + 1 + game_state->button_count;
        }
    
        SimpleImage bg;

        int amount_of_mobs = 0;
    
        int current_surface = 0;
        int time_since_surface_changed = 0;
    
        State *game_state;
        bool cw_debug = false;
        
        int currentKey = 'w';
        bool state_changed = true;

        DrawingSurface extra_surface_1;
        DrawingSurface extra_surface_2;
        DrawingSurface extra_surface_3;

        //FilterPointScrolling scrolling_filter;
};

#endif
