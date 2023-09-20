#pragma once
#include "StateMenu.h"
#include "UIButton.h"

class UIExitButton : public UIButton {
public:
    UIExitButton(State *p, std::string l) : UIButton(p, new StateMenu(), l) {}
    void additionButtonAction() override;
};
