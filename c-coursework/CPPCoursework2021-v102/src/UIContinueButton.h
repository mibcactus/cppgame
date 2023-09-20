#pragma once
#include "StateLevel.h"
#include "UIButton.h"

class UIContinueButton : public UIButton {
    public:
        UIContinueButton(State *b, StateLevel *s) : UIButton(b, s, "CONTINUE") {
            m_iCurrentScreenX = b->engine->getWindowWidth()/2;
            m_iCurrentScreenY = b->engine->getWindowHeight()/2;
        }

    private:
        void additionButtonAction() override {
            getEngine()->unpause();
        }
};
