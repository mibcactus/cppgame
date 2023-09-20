#pragma once
#include "Entity.h"
#include "State.h"

class UIButton : public Entity {
    public:
        UIButton(State *t, State *s, std::string l) : Entity(t) {
            new_state = s;
            label = l;
            getEngine()->notifyObjectsAboutMouse(true);
            //box_width = label.length()*24;
            //box_height = 50;
            m_iDrawWidth = label.length()*24;
            m_iDrawHeight = 50;
        }

        ~UIButton() {
            if(new_state && delete_state)
                delete new_state;
        }
    
        void setStateAndLabel(State *s, std::string l) {
            new_state = s;
            label = l;
        }
        void virtDraw() override;

        void virtMouseDown(int iButton, int iX, int iY) override;
        virtual void additionButtonAction();
    
        void virtDoUpdate(int iCurrentTime) override;

    protected:
        bool delete_state = true;
        std::string label;
        State *new_state;
        int timesclicked = 0;
        int textColour = 0x000000;
        int boxColour;
        //int box_width;
        //int box_height;
};
