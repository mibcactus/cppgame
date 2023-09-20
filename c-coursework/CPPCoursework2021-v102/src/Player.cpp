#include "Psymp12Engine.h"
#include "Player.h"

#include "Bullet.h"
#include "FGDetail.h"
#include "StateLose.h"

void Player::virtDraw() {
    if(!anim) {
        texture.renderImageWithMask(
            getEngine()->getForegroundSurface(),
            0,0,
            getScreenX(), getScreenY(),
            texture.getWidth(), texture.getHeight()
            );
    } else {
        anim->drawCurrentFrame();
    }

    if(getEngine()->getModifiedTime() < timeWhenHit + 500) {
        explosion.renderImageWithMask(getEngine()->getForegroundSurface(), 0,0, getScreenX() + 16, getScreenY()-20, 30,30);
    }
}


void Player::virtDoUpdate(int iCurrentTime) {
    
    //printf("In player update area\n");
    Psymp12Engine* engine = static_cast<Psymp12Engine*>(getEngine());

    if(current_hp == 0) {
        engine->state_changed = true;
        engine->transitionTo(new StateLose());
        return;
    }
    
    moving_x = 0;
    moving_y = 0;
    if(engine->isKeyPressed('w')) {
        moving_y -= 1;
    }
    if(engine->isKeyPressed('s')) {
        moving_y += 1;
    }
    if(engine->isKeyPressed('a')) {
        moving_x -= 1;
    }
    if(engine->isKeyPressed('d')) {
        moving_x += 1;
    }

    // move velocity towards 0 if button not pressed
    if(moving_x == 0) {
        if(x_velocity < 0) {
            x_velocity += speed;
        } else {
            x_velocity -= speed;
        }
    }
    
    if(moving_y == 0) {
        if(y_velocity < 0) {
            y_velocity += speed;
        } else {
            y_velocity -= speed;
        }
    }

    // find new velocity
    x_velocity += speed * moving_x;
    y_velocity += speed * moving_y;

    // clamps the velocity if needed
    if(x_velocity > max_speed) {
        x_velocity = max_speed;
    } else if (x_velocity < max_speed*-1) {
        x_velocity = max_speed*-1;
    }
    if(y_velocity > max_speed) {
        y_velocity = max_speed;
    } else if (y_velocity < max_speed*-1) {
        y_velocity = max_speed*-1;
    }

    //printf("Current velocity: (%d, %d)\n", x_velocity, y_velocity);

    // check player is standing on a tile
    //screen is 14x28 tiles i think
    int new_pos_x = (speed * moving_x);
    int new_pos_y =(speed * moving_y);
    
    int tile_pos_x = (position_x + new_pos_x + 32)/80 % 27; 
    int tile_pos_y = (position_y + new_pos_y + 60)/80 % 13;
    int tile = level->tilemap[tile_pos_y][tile_pos_x];

    // used to update the tiles and player position
    if(tile == 0) {
        new_pos_x = 0;
        new_pos_y = 0;
    } else if (tile == 19) {
        level->tilechanged_x = level->spawnerTile_x;
        level->tilechanged_y = level->spawnerTile_y;
        level->tilechanged_location_x = level->tilechanged_x*80;
        level->tilechanged_location_y = level->tilechanged_y*80;
        level->tilemap_changed = true;
    } else if (tile == 20 && iCurrentTime > level->timeWhenSpawned + 200) {
        level->timeWhenSpawned = iCurrentTime;
        //spawns bullets
        level->bullets.appendObjectToArray(new Bullet(level,
            -1, 0,
            tile_pos_x*80 + 40, tile_pos_y*80 + 40));

        level->bullets.appendObjectToArray(new Bullet(level,
            0, -1,
            tile_pos_x*80 + 40, tile_pos_y*80 + 40));

        level->bullets.appendObjectToArray(new Bullet(level,
            0, 1,
            tile_pos_x*80 + 40, tile_pos_y*80 + 40));
        level->bullets.appendObjectToArray(new Bullet(level,
            1, 0,
            tile_pos_x*80 + 40, tile_pos_y*80 + 40));
    }

    // check player isn't colliding with a fg detail
    
    
    
    //if(estate)
    position_x += new_pos_x;
    position_y += new_pos_y;
    
    int bul_x = 0, bul_y = 0;
    if(engine->isKeyPressed(SDLK_UP))
        bul_y += 1;
    if(engine->isKeyPressed(SDLK_DOWN))
        bul_y -= 1;
    if(engine->isKeyPressed(SDLK_LEFT))
        bul_x += 1;
    if(engine->isKeyPressed(SDLK_RIGHT))
        bul_x -= 1;
    
    // only fires a bullet if the arrow keys are pressed
    if((bul_x != 0 || bul_y != 0) && engine->getModifiedTime() > timeWhenAttacked + 100) {
        level->bullets.appendObjectToArray(new Bullet(level,
            bul_x, bul_y,
            position_x+20, position_y+32));
        timeWhenAttacked = engine->getModifiedTime();
    }

    // checks players collision with mobs
    draw_explosion = false;
    if(colliding_hitbox && engine->getModifiedTime() > timeWhenHit + 500) {
            timeWhenHit = getEngine()->getModifiedTime();
            //time_explosion_drawn = 0;
            draw_explosion = true;
            current_hp--;
    }
    

    if(moving_x || moving_y) {
        if(anim)
            anim->updateFrame(iCurrentTime);
    }
    
    if(getScreenX() > engine->getWindowWidth()/2 + 150 && position_x < engine->bg.getWidth()){
            level->x_offset += speed;
    } else if (getScreenX() < engine->getWindowWidth()/2 - 150 && position_x > 500) { // checks the left side of the screen
            level->x_offset -= speed;   
    }
    
    

    
    //update after finding out the final position
    m_iCurrentScreenX = position_x - level->x_offset;
    m_iCurrentScreenY = position_y - level->y_offset;
    //setScreenPosition(getScreenX(), getScreenY());
    
    checkBoundaries();
    
    redrawDisplay();
}




