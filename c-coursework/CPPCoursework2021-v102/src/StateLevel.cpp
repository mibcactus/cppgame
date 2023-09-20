#include "StateLevel.h"

#include "BGDetail.h"
#include "Enemy.h"
#include "FGDetail.h"
#include "Goober.h"
#include "Hearts.h"
#include "MobsLeft.h"
#include "Player.h"
#include "Psymp12Engine.h"
#include "StateLevelData.h"
#include "StateMenu.h"
#include "StatePause.h"
#include "StateWin.h"
#include "UIButton.h"
#include "UtilPixelCollision.h"

class Enemy;
class Player;

StateLevel::~StateLevel() {
    bullets.destroyOldObjects(true);
    if(engine != nullptr)
        engine->destroyOldObjects(true);
}

void StateLevel::mainLoopBeforeUpdate() {
    x_offset += x_update_offset;
    y_offset += y_update_offset;

    // clamps the offset if needed
    int surface_width = engine->getForegroundSurface()->getSurfaceWidth();
    if(x_offset > surface_width) {
        x_offset = surface_width;
    }
    else if(x_offset < -surface_width) {
        x_offset = -surface_width;
    }
    engine->redrawDisplay();
}


void StateLevel::copyAllBackgroundBuffer() {
    DrawingSurface* s = engine->getForegroundSurface();
    DrawingSurface* b = engine->getBackgroundSurface();
    int winw = engine->getWindowWidth();
    int winh = engine->getWindowHeight();

    // scrolls the bg
    s->copyRectangleFrom(b, 0, 0, winw, winh, x_offset, 0);
    s->copyRectangleFrom(b, 0, 0, winw, winh, x_offset - winw, 0);
}


void StateLevel::onPause() {
    engine->pause();

    StateLevelData level_data;

    // save player data
    Player* p = static_cast<Player*>(engine->getDisplayableObject(0));
    level_data.player_hp = p->current_hp;
    level_data.player_x = p->getScreenX();
    level_data.player_y = p->getScreenY();

    // save enemy data
    level_data.mob_amount = 0;
    for(int i = 1; i < mob_count + 1; i++) {
        MobData temp;
        Enemy* mob = static_cast<Enemy*>(engine->getDisplayableObject(i));
        temp.hp = mob->current_hp;
        //temp.mob_position = mob->movement_position;
        temp.mob_x = mob->getScreenX();
        temp.mob_y = mob->getScreenY();
        temp.mob_texture = mob->getTexture();
        temp.y_sort = i;

        temp.in_range = mob->in_range;
        temp.moving = mob->is_moving;
        temp.type = mob->type;

        level_data.addMobData(temp);
    }

    // transition to new state
    level_data.level_ID = level_ID;
    level_data.x_offset = x_offset;
    level_data.y_offset = y_offset;
    level_data.initialised = true;

    State* new_state = new StatePause(level_data);

    engine->drawableObjectsChanged();
    engine->destroyOldObjects(true);

    bullets.drawableObjectsChanged();
    bullets.destroyOldObjects(true);

    engine->state_changed = true;
    engine->transitionTo(new_state);
}

void StateLevel::drawBG() {
    renderBGimage();
    renderSubclassBG();
}

void StateLevel::renderSubclassBG() {
    int start_y = 0;
    for(int i = 0; i < 13; i++) {
        int start_x = 0;
        for(int j = 0; j < 16; j++) {
            if(tilemap[i][j] != 0) {
                tile_manager.drawGivenTile(engine, tilemap[i][j], start_x, start_y);
            }
            start_x += 80;
        }

        start_y += 80;
    }
}

void StateLevel::postDrawFG() {
        if(draw_mob_hit) {
            drawMobHitEffect();
        }
        if(draw_player_hit) {
            drawPlayerHitEffect();
        }
}


void StateLevel::drawMobHitEffect() {/*
    Entity *mob = dynamic_cast<Entity*>(engine->getDisplayableObject(mob_hit));
    explosion.renderImageWithMask(engine->getForegroundSurface(), 0,0, mob->getScreenX(), mob->getScreenY()-(mob->getDrawWidth()/2), 30, 30);*/
}


void StateLevel::drawPlayerHitEffect() {
    /*
    Player *mob = dynamic_cast<Player*>(engine->getDisplayableObject(0));
    explosion.renderImage(engine->getForegroundSurface(),
        0,0, mob->getScreenX(), mob->getScreenY()-(mob->getDrawWidth()/2), 30, 30);*/
}


void StateLevel::renderBGimage() {
    engine->bg = ImageManager::get()->getImagebyURL(bgurl, true, true);
    engine->bg.renderImage(engine->getBackgroundSurface(), 0, 0, 0, 0, engine->bg.getWidth(), engine->bg.getHeight());

    BGDetail trees = BGDetail(engine, BGDetail_Type::TREE);
    trees.drawBG(320);

}


void StateLevel::checkCollision() {
    Player* p = dynamic_cast<Player*>(engine->getDisplayableObject(0));

    // checks players collision with mobs
    p->colliding_hitbox = false;
    if(engine->getModifiedTime() > collision_time + 10) {
        for(int i = 1; i <= mob_count; i++) {
            Enemy* mob = dynamic_cast<Enemy*>(engine->getDisplayableObject(i));
            mob->colliding_hitbox = false;
            //if(PixelCollision::checkPixelCollisionWithEntity(p, mob)) {
            /*
            if(p != nullptr) {
                printf("player exists :)\n");
            } else {
                printf("no player found...\n");
            }
            if(mob != nullptr) {
                printf("mob exists!:)\n");
            } else {
                printf("no mob found....\n");
            }*/
            if(*p % *mob) {
                p->colliding_hitbox = true;
                mob->colliding_hitbox = true;
                additionalCollisionActions(); //hook for subclasses to do stuff
                collision_time = engine->getModifiedTime();
            }
        }
    }
}


void StateLevel::preDrawFG() {
    if(engine->cw_debug) {
        if(data.initialised) {
            std::string str = data.playerDataString();
            engine->drawForegroundString(50, 150, str.c_str(), 0xff00ff);
        }
    }
}


void StateLevel::mainLoopStart() {
    // check collision
    checkCollision();
    if(mob_count < 1) {
        allMobsDead();
    }
}

void StateLevel::allMobsDead() {
    engine->state_changed = true;
    engine->transitionTo(new StateWin(this->level_ID));
}


void StateLevel::saveStateData() {
    StateLevelData level_data;

    level_data.level_ID = this->level_ID;

    // save player data
    Player* p = static_cast<Player*>(engine->getDisplayableObject(0));
    level_data.player_hp = p->current_hp;
    level_data.player_x = p->getPosX();
    level_data.player_y = p->getPosY();

    // save enemy data
    level_data.mob_amount = 0;
    for(int i = 1; i < mob_count + 1; i++) {
        MobData temp;
        Enemy* mob = static_cast<Enemy*>(engine->getDisplayableObject(i));
        temp.hp = mob->current_hp;
        //temp.mob_position = mob->movement_position;
        temp.mob_x = mob->getPosX();
        temp.mob_y = mob->getPosY();
        temp.mob_texture = mob->getTexture();
        temp.y_sort = i;

        temp.in_range = mob->in_range;
        temp.moving = mob->is_moving;
        temp.type = mob->type;

        level_data.addMobData(temp);
    }

    // save foreground details
    for(int i = mob_count + 1; i < mob_count + fg_count + 1; i++) {
        fg_data temp;
        FGDetail* detail = dynamic_cast<FGDetail*>(engine->getDisplayableObject(i));
        temp.fg_type = detail->type;
        temp.fg_x = detail->getPosX();
        temp.fg_y = detail->getPosY();
        temp.y_sort = i;

        level_data.addDetailData(temp);
    }

    // transition to new state
    level_data.initialised = true;

    State* new_state = new StatePause(level_data);

    engine->state_changed = true;
    engine->transitionTo(new_state);
}

void StateLevel::debugText() {
    Player* p = dynamic_cast<Player*>(engine->getDisplayableObject(0));
    int colour = 0x70afb4;
    char buf[64];
    sprintf_s(buf, "Amount of bullets: %d", bullets.getContentCount());
    engine->drawForegroundString(50, 190, buf, colour);

    /*
    char buf1[64];
    sprintf_s(buf1, "Player HP: %d", p->current_hp);
    engine->drawForegroundString(50, 210, buf1, colour);
    */

    char buf2[64];
    sprintf_s(buf2, "Player screen position: (%d, %d)",
              p->getScreenX(),
              p->getScreenY());
    engine->drawForegroundString(50, 210, buf2, colour);

    char buf4[128];
    sprintf_s(buf4, "Player m_icurrent position: (%d, %d)", p->getM_ICurrentX(), p->getM_ICurrentY());
    engine->drawForegroundString(50, 230, buf4, colour);

    char buf3[64];
    sprintf_s(buf3, "Player surface position: (%d, %d)", p->getPosX(), p->getPosY());
    engine->drawForegroundString(50, 250, buf3, colour);

    char buf5[64];
    sprintf_s(buf5, "level offset: %d, %d", x_offset, y_offset);
    engine->drawForegroundString(50, 270, buf5, colour);

    char buf6[64];
    sprintf_s(buf6, "Player offset: %d, %d", p->getPosX() - p->getScreenX(), p->getPosY() - p->getScreenY());
    engine->drawForegroundString(50, 290, buf6, colour);

    engine->drawBackgroundRectangle(p->getPosX() - 5, p->getPosY() - 5, p->getPosX() + 5, p->getPosY() + 5, colour);
    engine->drawBackgroundRectangle(p->getScreenX() - 5, p->getScreenY() - 5, p->getScreenX() + 5, p->getScreenY() + 5,
                                    colour / 2);
}


void StateLevel::initObjects() {
    if(fromPause) {
        mob_count = data.mob_amount;
        x_offset = data.x_offset;
        y_offset = data.y_offset;


        displayable_object_count = 1 + mob_count + fg_count + button_count;
        engine->createObjectArray(getObjectCount());

        Player* player = new Player(this);
        //player->setPosition(data.player_x, data.player_y);
        player->setSurfacePosition(data.player_x, data.player_y);
        player->current_hp = data.player_hp;
        engine->storeObjectInArray(0, player);

        for(int i = 0; i < data.mob_amount; i++) {
            MobData current_mob_data = data.mob_data.at(i);

            //animations for goobers don't get set here
            Enemy* enemy = new Enemy(this, current_mob_data.mob_texture, player);
            enemy->type = current_mob_data.type;
            if(enemy->type == EnemyType::GOOBER) {
                enemy->anim = new Animation(enemy, ImageManager::loadImage("resources/goobsheet.png"), 4, 1);
            }
            enemy->current_hp = current_mob_data.hp;
            enemy->setSurfacePosition(current_mob_data.mob_x, current_mob_data.mob_y);
            enemy->setScreenPosition(enemy->getPosX() + x_offset, enemy->getPosY() + y_offset);

            enemy->y_sort = current_mob_data.y_sort;
            enemy->in_range = current_mob_data.in_range;
            enemy->is_moving = current_mob_data.moving;
            engine->storeObjectInArray(current_mob_data.y_sort, enemy);
        }

        //std::cout << "successfully initalised from pause\n";

    }
    else {
        initialiseMobsNormally();
    }
    initialiseBulletsArray();
    addForegroundElements();
    addUIbuttons();
    //std::cout << "everything has been initialised\n";
}

void StateLevel::initialiseBulletsArray() {
    bullets.createObjectArray(displayable_object_count);
}


void StateLevel::initialiseMobsNormally() {
    mob_count = 2;
    //engine->amount_of_mobs = mob_count;
    engine->createObjectArray(getObjectCount());

    Player* player = new Player(this);
    player->setScreenPosition(100, 900);
    engine->storeObjectInArray(0, player);

    Goober* enemy = new Goober(this, player);
    enemy->setSurfacePosition(1200, 700);
    engine->storeObjectInArray(1, enemy);

    Goober* goober = new Goober(this, player);
    goober->setSurfacePosition(300, 770);
    engine->storeObjectInArray(2, goober);
}

void StateLevel::drawAllTemporaryObjects() {
    bullets.drawAllBullets();
}

void StateLevel::updateAllTemporaryObjects() {
    bullets.updateAllBullets(engine->getModifiedTime());
}


void StateLevel::addForegroundElements() {
    int index = 1 + mob_count;
    FGDetail* camp1 = new FGDetail(this, FGDetail_type::CAMP);
    camp1->setSurfacePosition(1000, 750);
    engine->storeObjectInArray(index, camp1);
}

void StateLevel::addHeartsAndMobCounter() {
    Hearts* hearts = new Hearts(this);
    engine->storeObjectInArray(getObjectCount() - 2, hearts);

    MobsLeft* mobs_left = new MobsLeft(this);
    engine->storeObjectInArray(getObjectCount() - 3, mobs_left);
}

void StateLevel::addMenuButton() {
    StateMenu* menu = new StateMenu();
    menu->setEngine(engine);
    UIButton* menuButton = new UIButton(this, menu, "MENU");
    menuButton->setScreenPosition(100, engine->getWindowHeight() - 100);
    engine->storeObjectInArray(getObjectCount() - 1, menuButton);
}
