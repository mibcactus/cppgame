#include "Enemy.h"
#include "Bullet.h"
#include "UtilPixelCollision.h"

bool Enemy::playerInRange(int eX, int eY, int pX, int pY) const {
    int diff_x = eX - pX;
    diff_x = diff_x < 0 ? diff_x*-1 : diff_x;
    
    int diff_y = eY - pY;
    diff_y = diff_y < 0 ? diff_y*-1 : diff_y;
    
    if(diff_x <= range && diff_y <= range) {
        return true;
    }

    return false;
}

void Enemy::checkCollisionWithPlayer() {
    colliding_hitbox = *this % *player;
}

void Enemy::checkCollisionWithBullets() {
    int count = level->bullets.getContentCount();
    for(int i = 0; i < count; i++) {
        auto b = dynamic_cast<Bullet*>(level->bullets.getDisplayableObject(i));
        if(b) {
            //bool colls = PixelCollision::checkPixelCollisionWithEntity(this, b);
            bool colls = *this % *b;
            // printf("checking collision, array count: %d\n", i);
            if(colls && getEngine()->getModifiedTime() > timeWhenHit + 100 ) {
                // std::cout << "COLLIDING!\n";
                current_hp -= b->damage;
                timeWhenHit = getEngine()->getModifiedTime();
                b->colliding_hitbox = true;
                break;
            }
        }
    }
    
}


void Enemy::virtDoUpdate(int iCurrentTime) {
    Psymp12Engine *engine = dynamic_cast<Psymp12Engine*>(getEngine());
    if(engine->state_changed) {
        delete this;
    }
    if(iCurrentTime > time_since_hit +  100) {
        checkCollisionWithBullets();
    }
    
    in_range = playerInRange(position_x, position_y, player->getPosX(), player->getPosY());

    if(in_range) {
        target_x = player->getPosX();
        target_y = player->getPosY();

        const int x_diff = target_x - position_x;
        const int y_diff = target_y - position_y;

        if(x_diff > 0) {
            velocity_x += 1;
            anim->flip = false;
        } else if (x_diff < 0) {
            velocity_x -= 1;
            anim->flip = true;
        }

        if(y_diff > 0) {
            velocity_y += 1;
        } else if (y_diff < 0) {
            velocity_y -= 1;
        }

        moving_time++;
        if(moving_time < random_time_boundary) {
            velocity_x *= distance/125;
            velocity_y *= distance/125;
        } else if (moving_time < random_time_boundary*1.5) {
            velocity_x *= distance/-125;
            velocity_y *= distance/-125;
        } else {
            moving_time = 0;
        }
        

        position_x += velocity_x;
        position_y += velocity_y;
        
    }

    //initialiseAllPositions(position_x, position_y);
    setScreenPosition(position_x - level->x_offset, position_y-level->y_offset);
    updateAnimationHook(iCurrentTime);

    checkBoundaries();
    if (current_hp == 0) {
        getEngine()->removeDisplayableObject(this);
        level->mob_count--;
    }
    
    redrawDisplay();
    
    
}






