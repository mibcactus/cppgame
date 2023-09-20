#pragma once
#include "State.h"

class StateLose : public State {
    public:
        StateLose() : State() {
            state_name = "GAME OVER";
        }
        void drawBG() override;
        void postDrawFG() override;
        void initObjects() override;
    
};
