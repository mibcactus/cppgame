#pragma once
#include "State.h"

class StateScoreboard : State {
    public:
        StateScoreboard() : State() {
            state_name = "SCORES";
        }
        void drawBG() override;
        void initObjects() override;

    
};
