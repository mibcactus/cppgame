#pragma once
#include "State.h"

class StateMenu : public State {
    public:
        StateMenu() : State() {
            state_name = "MENU";
        }
    
        void drawBG() override;
        void initObjects() override;
};
