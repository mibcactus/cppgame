#pragma once
#include "StatePause.h"
#include "UIButton.h"

class UIPauseButton : public UIButton{
    public:
        UIPauseButton(State *p, State *s) : UIButton(p, s, "PAUSE") {
            
        }
    
};
