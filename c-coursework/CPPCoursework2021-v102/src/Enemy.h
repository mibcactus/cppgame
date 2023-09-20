#pragma once
#include "Entity.h"
#include "Player.h" 
#include "StateLevel.h"

class Enemy : public Entity {
#define MAX_DISTANCE 150
#define MIN_DISTANCE 50
#define MAX_TIME 175
#define MIN_TIME 100
    public:
        //Enemy(BaseEngine *b):Entity(b){colour = 0x304050;}
        //Enemy(BaseEngine *b, int xStart, int yStart, bool corner):Entity(b, xStart, yStart, corner){colour = 0xA94050;}

        Enemy(StateLevel *l, SimpleImage t, Player *p):Entity(l) {
            colour = 0x304050;
            texture = t;
            m_iDrawWidth = texture.getWidth();
            m_iDrawHeight = texture.getHeight();
            player = p;
            level = l;
            distance = MAX_DISTANCE;
            random_time_boundary = MAX_TIME;
            max_hp = 5;
            current_hp = max_hp;
        }

        Enemy(StateLevel *l, std::string url, Player *p):Entity(l) {
            colour = 0x304050;
            texture = ImageManager::loadImage(url, false);
            m_iDrawWidth = texture.getWidth();
            m_iDrawHeight = texture.getHeight();
            player = p;
            texture_url = url;
            level = l;
            distance = MAX_DISTANCE;
            random_time_boundary = MAX_TIME;
            max_hp = 5;
            current_hp = max_hp;
        }

        ~Enemy() {
            //printf("Entity size: %d\n", sizeof(this));
        }
    
        StateLevel *level;
    

        //void virtDraw() override;
        bool playerInRange(int eX, int eY, int pX, int pY) const;
        void virtDoUpdate(int iCurrentTime) override;
    
        std::string texture_url;

        Player *player;

        int range = 200;
        bool is_moving = false;
        bool in_range = false;
        
        
        int target_x = 0;
        int target_y = 0;
        int time_since_hit = 0;
        int moving_time = 0;
        int random_time_boundary;
        int distance;
        
        int velocity_x = 0, velocity_y = 0;

        EnemyType type;
    
    protected:
        friend bool playerInRange(int pX, int pY);
        void checkCollisionWithPlayer();
        void checkCollisionWithBullets();
    
};
