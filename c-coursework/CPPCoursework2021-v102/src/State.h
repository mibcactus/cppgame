#pragma once
#include <string>
#include <iostream>

class Psymp12Engine;

class State {
    public:
        virtual ~State() {

           // std::cout << "State :" << state_name << " destroyed.\n";
        }
        void setEngine(Psymp12Engine* e){engine = e;}

        //virtual void onClick();
        Psymp12Engine* engine;

        virtual void setUpBGDetailSurface(){}
        virtual void setUpTileSurface(){}
        virtual void setUpMobSurface(){}
    
        virtual void drawBG() = 0;

        virtual void mainLoopStart(){}
        virtual void mainLoopBeforeUpdate(){}
        virtual void mainLoopPostUpdate(){}
    
        virtual void preDrawFG() {}
        virtual void postDrawFG() {}
        virtual void drawAllTemporaryObjects() {}
        virtual void updateAllTemporaryObjects(){}
        //virtual void initalise() = 0;
        virtual void initObjects() = 0;
        virtual void onPause(){}

        virtual void copyAllBackgroundBuffer();

        int getObjectCount() {
            return mob_count+button_count+fg_count+1;
        }
        int mob_count = 2;
        int button_count = 2;
        int fg_count = 2;
        int displayable_object_count = mob_count+button_count+fg_count+1;
        std::string state_name = "STATE";
    
        virtual void debugText(){}
        //virtual void drawPreDraw() = 0;

    // used for scrolling
        int x_offset = 0;
        int y_offset = 0;

        int x_update_offset = 0;
        int y_update_offset = 0;

    // used for zooming
        int zoom_level = 0;
        
};
