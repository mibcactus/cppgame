
#include "UIButton.h"
#include "Psymp12Engine.h"

void UIButton::additionButtonAction() {
    
}


void UIButton::virtMouseDown(int iButton, int iX, int iY) {
    const int mouse_clicked_x = getEngine()->getMouseXClickedDown();
    const int mouse_clicked_y = getEngine()->getMouseYClickedDown();
    if(virtIsPositionWithinObject(mouse_clicked_x, mouse_clicked_y)) {
        additionButtonAction();
        delete_state = false;
        dynamic_cast<Psymp12Engine*>(getEngine())->state_changed = true;
        dynamic_cast<Psymp12Engine*>(getEngine())->transitionTo(new_state);
    }
}


void UIButton::virtDraw() {
    int x = m_iCurrentScreenX;
    int y = m_iCurrentScreenY;

    int length = label.length()*24;
    int height = 50;
    
    getEngine()->drawForegroundRectangle(x,y, x+length, y+height, 0x00000);
    getEngine()->drawForegroundRectangle(x+5, y+5, x+length-5, y+height-5, colour);
    getEngine()->drawForegroundString(x+10, y+10, label.c_str(), textColour, NULL);
}

void UIButton::virtDoUpdate(int iCurrentTime) {
    // TODO: Implement stuff, eg put animations in here or something
    redrawDisplay();
}




