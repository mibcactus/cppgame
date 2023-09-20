#pragma once
#include "Animation.h"
#include "Entity.h"
#include "StateLevel.h"
#include "UtilEnums.h"

class Player : public Entity {
    public:
        Player(StateLevel *l) : Entity(l) {
            m_iDrawWidth = 16;
            m_iDrawHeight = 32;
            current_hp = 5;
            texture = ImageManager::loadImage("resources/player.png", true);
            position_x = 500;
            position_y = 800;
            setScreenPosition(getScreenX(), getScreenY());
            level = l;
            anim = new Animation(this, ImageManager::loadImage("resources/player sheet.png"), 5, 1, 2);
            //*currentAnimation = walk_animation;
        }
    
        int speed = 2;
        int max_speed = 2;
        int x_velocity = 0, y_velocity = 0;
    
        void virtDoUpdate(int iCurrentTime) override;
        void virtDraw() override;
        StateLevel *level;
    
        Directions direction = Directions::DOWN;
        int moving_x = 0; // -1 is left, 1 is right
        int moving_y = 0; // -1 is up, 1 is down

        int max_explosion_time = 200;
        int time_explosion_drawn = 0;
        bool draw_explosion = false;
        
    
        //PlayerData player_data;
        std::string text_url = "resources/player.png";
    
    // for animation rendering
        bool moving = false;
        //SimpleImage spritesheet;
    
        
        //Animation *walk_animation;
        /*
        Animation death_animation;
        Animation win_animation;
        */
    
        //Animation *currentAnimation;
};
