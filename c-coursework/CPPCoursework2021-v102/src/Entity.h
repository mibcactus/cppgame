#pragma once

#include "Psymp12Engine.h"
#include "DisplayableObject.h"
#include "StateLevel.h"


class Animation;

// base class for all interactable objects in the game
class Entity : public DisplayableObject {
    public:
        Entity(State *l) : DisplayableObject(400, 500, l->engine, 80,80, true) {
            state = l;
            position_x = 400;
            position_y = 500;
            m_iCurrentScreenX = 400;
            m_iCurrentScreenY = 500;
            setShouldDeleteOnRemoval(true);
        }
        Entity(State *l, int xStart, int yStart, bool corner) : DisplayableObject(xStart, yStart, l->engine, 80,80, corner) {
            state = l;
            position_x = xStart;
            position_y = yStart;
            m_iCurrentScreenX = 400;
            m_iCurrentScreenY = 500;
            setShouldDeleteOnRemoval(true);
        }
        Entity(State *l, int width, int height): DisplayableObject(400, 500, l->engine, width, height, true) {
            state = l;
            position_x = 400;
            position_y = 500;
            m_iCurrentScreenX = 400;
            m_iCurrentScreenY = 500;
            setShouldDeleteOnRemoval(true);
        }
        Entity(State *l, SimpleImage t) : DisplayableObject(500,500,l->engine,t.getWidth(),t.getHeight(), true){
            texture = t;
            m_iDrawWidth = t.getWidth();
            m_iDrawHeight = t.getHeight();
            state = l;
            position_x = 400;
            position_y = 500;
            m_iCurrentScreenX = 400;
            m_iCurrentScreenY = 500;
            setShouldDeleteOnRemoval(true);
        }

        ~Entity();

        State *state;
    
        void virtDraw() override;
        void setColour(unsigned int c){colour=c;}

        void setScreenPosition(int x, int y) {
            m_iCurrentScreenX = x;
            m_iCurrentScreenY = y;
            //setSurfacePosition(x + state->x_offset, y+state->y_offset);
        }

        void setSurfacePosition(int x, int y) {
            position_x = x;
            position_y = y;
        }

        /*
         * Sets both the screen and surface positions using a given surface position
         */
        void initialiseAllPositions(int pos_x, int pos_y) {
            setScreenPosition(pos_x+state->x_offset, pos_y+state->y_offset);
            setSurfacePosition(pos_x, pos_y);
        }
    
        // ReSharper disable once CppInconsistentNaming
        int getM_ICurrentX(){return m_iCurrentScreenX;}
        int getM_ICurrentY(){return m_iCurrentScreenY;}
        int getScreenX() {
            return m_iCurrentScreenX;
            //return position_x + state->x_offset;
        }
        int getScreenY() {
            return m_iCurrentScreenY;
            //return position_y + state->y_offset;
        }

        int getPosX() {
            return position_x;
        }

        int getPosY() {
            return position_y;
        }

        

        //bool checkPixelCollision() const;
        int getPixel(int x, int y);

        SimpleImage getTexture() {
            return texture;
        }
        void setTexture(SimpleImage t) {
            texture = t;
        }

        virtual int getLocalXfromSurfaceX(int surface_x);

        virtual int getLocalYfromSurfaceY(int surface_y) ;
    
    
        virtual void checkBoundaries();
        bool colliding_hitbox = false;
        int max_hp;
        int current_hp;
        int y_sort; // used to decide what order to draw mobs and store them in the container
        int timeWhenHit = 0;
        int timeWhenAttacked = 0;

        int position_x = 0;
        int position_y = 0;

        Animation *anim = nullptr;
        int currentFrame = 0;
        void updateAnimationHook(int time);

    protected:
        SimpleImage texture;
        SimpleImage explosion = ImageManager::loadImage("resources/boom.png", true);
        unsigned int colour = 0x448893;
};
