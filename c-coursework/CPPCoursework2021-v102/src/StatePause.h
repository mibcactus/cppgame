#pragma once
#include <utility>

#include "State.h"
#include "StateLevel.h"
#include "StateLevelData.h"
#include "StateLevel_0.h"
#include "StateLevel_1.h"
#include "StateLevel_2.h"

class StatePause : public State{
    public:
        StatePause(StateLevelData d) : State() {
            level_data = std::move(d);
            state_name = "PAUSED";
        }

        void mainLoopBeforeUpdate() override;
        void copyAllBackgroundBuffer() override;
        void drawBG() override;
        void initObjects() override;
        void onPause() override;

        StateLevelData level_data;
    
    private:
        StateLevel* decideLevel() {
            StateLevel *level;
            switch(level_data.level_ID) {
                case 0:
                    level = new StateLevel_0();
                    break;
                case 1:
                    level = new StateLevel_1();
                    break;
                case 2:
                    level = new StateLevel_2();
                    break;
                default:
                    level = new StateLevel();
                    break;
            }
            return level;
        }

    
        int offset = 0;
        SimpleImage bg = ImageManager::loadImage("resources/win.png");
        SimpleImage frame = ImageManager::loadImage("resources/scroll frame.png");
        //void save_data();
};
