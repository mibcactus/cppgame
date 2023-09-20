#pragma once
#include "Animation.h"
#include "Entity.h"
#include "ImagePixelMapping.h"
#include "Psymp12ImagePixelMapping.h"
#include "UtilEnums.h"

class FGDetail : public Entity{
    public:

    FGDetail(State *l, FGDetail_type t, bool m = false) : Entity(l) {
            engine = l->engine;
            type = t;
            switch(t) {
                case FGDetail_type::CAMP:
                    texture = ImageManager::loadImage("resources/house.png");
                    anim = new Animation(this, ImageManager::loadImage("resources/camp sheet.png"), 3, 1);
                break;
                case FGDetail_type::HOUSE:
                    texture = ImageManager::loadImage("resources/house.png");
                    texture.setTransparencyColour(-1);
                break;
                case FGDetail_type::ROCK:
                    texture = ImageManager::loadImage("resources/bricks.png");
                break;
                case FGDetail_type::TREE:
                    texture = ImageManager::loadImage("resources/trees.png");
                break;
                default:
                    texture = ImageManager::loadImage("resources/camp.png");
                anim = new Animation(this, ImageManager::loadImage("resources/camp sheet.png"), 3, 1);
                break;
            }
            //std::cout <<"\n"; 
            m_iDrawWidth = texture.getWidth();
            m_iDrawHeight = texture.getHeight();
        }

        FGDetail_type type;
        Psymp12Engine *engine;
    
        void onCollide(){}
        /*void virtDraw() override {
            if(anim) {
                anim->drawCurrentFrame();
            } else {
                texture.renderImageWithMask(
                    engine->getForegroundSurface(),
                    0,0,
                    getScreenX(), getScreenY(),
                    texture.getWidth(), texture.getHeight());
            }
        }*/
        void virtDoUpdate(int iCurrentTime) override {
            if(colliding_hitbox) {
                onCollide();
            }
            setScreenPosition(position_x - state->x_offset, position_y-state->y_offset);
            if(anim) {
                updateAnimationHook(iCurrentTime);
            }
        }

        //bool mapping = false;
        /*void drawWithMapping() {
            int time = engine->getModifiedTime();
            int max = 20;
            int skew_width = time % max;
            texture.renderImageApplyingMapping(engine,
                engine->getForegroundSurface(),
                m_iCurrentScreenX, m_iCurrentScreenY,
                texture.getWidth(), texture.getHeight(),
                new ImagePixelMappingSkew(skew_width)
                );
        }
        int skew_direction = 1;*/
    
    
};
