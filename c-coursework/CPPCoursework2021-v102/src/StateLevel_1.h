﻿#pragma once
#include "StateLevel.h"

class StateLevel_1 : public StateLevel {
    public:
        StateLevel_1();

    //need to redraw BG, FG, reinitialise objects
        void renderBGimage() override;
        void copyAllBackgroundBuffer() override;
        void renderSubclassBG() override;
        //void allMobsDead() override;
        void initialiseMobsNormally() override;
        void mainLoopBeforeUpdate() override;
        //SimpleImage stars;

    int new_tilemap[13][27] = {
        {11,11,13,6,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,14,14,6,8,8,8},
        {11,11,11,13,6,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,11,11,7,8,8,8},
        {11,11,11,11,13,6,8,8,8,8,8,8,8,8,8,8,8,8,4,14,15,19,11,7,8,8,8},
        {2,2,3,11,11,13,6,8,8,8,8,8,8,8,8,8,8,8,9,11,11,11,11,7,8,8,8},

        {8,8,16,3,11,11,13,5,6,8,8,8,8,8,8,8,8,8,9,11,11,11,1,18,8,8,8},
        {8,8,8,16,3,11,11,11,13,14,14,14,6,8,8,8,8,8,16,2,2,2,18,8,8,8,8},
        {8,8,8,8,16,3,11,11,11,11,11,11,13,6,8,8,8,8,8,8,8,8,8,8,8,8,8},
        {8,8,8,8,8,9,11,11,11,11,11,11,11,13,14,14,14,14,14,14,14,14,6,8,8,8,8},

        {8,8,8,8,8,16,3,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,13,5,14,5,6},
        {8,8,8,8,8,8,16,2,2,2,2,2,2,2,3,11,11,11,11,1,2,3,11,11,11,11,13},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,16,2,2,2,2,18,8,16,2,3,11,11,11},
        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,16,3,11,11},

        {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,11,11}};
};