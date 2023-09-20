#pragma once
#include "State.h"
#include "StateEnd.h"
#include "StateLevel_1.h"
#include "StateLevel_2.h"

class StateWin : public State {
public:
    StateWin(int prev_ID) : State() {
        state_name = "WIN";
        new_level = decideLevel(prev_ID);
        
    }
    
    void drawBG() override;
    void initObjects() override;
    
    StateLevel* decideLevel(int level_ID) {
        StateLevel *level;
        switch(level_ID) {
            case 0:
                level = new StateLevel_1();
                break;
            case 1:
                level = new StateLevel_2();
                break;
            default:
                level = new StateLevel_2();
                break;
        }
        return level;
    }

    StateLevel* new_level;
    
};
