#pragma once
#include "Bullet.h"
#include "Entity.h"
#include "UtilCollisionDetection.h"

class PixelCollision {
    public:
        PixelCollision() = delete;
    
        static bool checkPixelCollisionWithEntity(Entity *r, Entity *e) {
            // goes thru every pixel in the first entity and sees if any of e's pixels are there
            if(!r || !e) {
                return false;
            }

            for(int i = r->getScreenX(); i < r->getDrawWidth() + r->getScreenX(); i++) {
                for(int j = r->getScreenY(); j < r->getDrawHeight() + r->getScreenY(); j++) {
                    if(e->virtIsPositionWithinObject(i, j)) { //virt position x uses screen positions
                        return true;
                    }
                    
                }
            }
            return false;
        }
};

inline bool operator%(Entity &mob, Bullet &bullet) {
    const int b_left = bullet.getPosX(); const int b_right = b_left + bullet.getDrawWidth();
    const int m_left = mob.getPosX(); const int m_right = m_left + mob.anim->sprite_width;
    const int b_top = bullet.getPosY(); const int b_bottom = b_top + bullet.getDrawHeight();
    const int m_top = mob.getPosY(); const int m_bottom = m_top + mob.anim->sprite_height;
    
    // first checks if there's even any overlap, no point doing the rest if theres no overlap
    if(!CollisionDetection::checkRectangles(m_left, m_right, m_top, m_bottom, b_left, b_right, b_top, b_bottom)) {
        return false;
    }

    const unsigned int r_trans = -1, e_trans = -1;

    for(int y = m_top; y < m_bottom; y++) {
        for(int x = m_left; x < m_right; x++) {
            const int rx_local = mob.getLocalXfromSurfaceX(x);
            const int ry_local = mob.getLocalYfromSurfaceY(y);
            const unsigned int r_colour = mob.getPixel(rx_local, ry_local);

            const int ex_local = bullet.getLocalXfromSurfaceX(x);
            const int ey_local = bullet.getLocalYfromSurfaceY(y);
            const unsigned int e_colour = bullet.getPixel(ex_local, ey_local);

            if(r_colour != r_trans && e_colour != e_trans) {
                return true;
            }
            
        }
    }
    
    return false;
}

inline bool operator%(Entity &r, Entity &e) {
    const int e_left = e.getPosX(); const int e_right = e_left + e.anim->sprite_width;
    const int r_left = r.getPosX(); const int r_right = r_left + r.anim->sprite_width;
    const int e_top = e.getPosY(); const int e_bottom = e_top + e.anim->sprite_height;
    const int r_top = r.getPosY(); const int r_bottom = r_top + r.anim->sprite_height;
    
    // first checks if there's even any overlap
    if(!CollisionDetection::checkRectangles(r_left, r_right, r_top, r_bottom, e_left, e_right, e_top, e_bottom)) {
        return false;
    }

    // gets screen positions of where to start checking
    unsigned int r_colour, e_colour, r_trans, e_trans;
    r_trans = 0x000000; e_trans = 0x000000;

    for(int y = r_top; y < r_bottom; y++) {
        for(int x = r_left; x < r_right; x++) {
            int rx_local, ry_local;
            int ex_local, ey_local;
            rx_local = r.getLocalXfromSurfaceX(x);
            ry_local = r.getLocalYfromSurfaceY(y);
            r_colour = r.getPixel(rx_local, ry_local);

            ex_local = e.getLocalXfromSurfaceX(x);
            ey_local = e.getLocalYfromSurfaceY(y);
            e_colour = e.getPixel(ex_local, ey_local);

            if(r_colour != -1 && e_colour != -1) {
                e.colliding_hitbox = true;
                return true;
            }
            
        }
    }
    
    return false;
}
     




