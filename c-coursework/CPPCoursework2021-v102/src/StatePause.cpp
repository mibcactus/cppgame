#include "StatePause.h"

#include "StateLevel.h"
#include "UIButton.h"
#include "UIContinueButton.h"

void StatePause::onPause() {
    StateLevel *level = decideLevel();
    level->data = level_data;
    level->fromPause = true;
    
    
    engine->state_changed = true;
    engine->unpause();
    engine->transitionTo(level);
}


void StatePause::drawBG() {
    bg.renderImage(engine->getBackgroundSurface(), 0,0,0,0, bg.getWidth(), bg.getHeight());
    frame.renderImageWithMask(engine->getBackgroundSurface(),0,0,0,0, frame.getWidth(), frame.getHeight(), 0);
    int x = engine->getWindowWidth()/2 - (3*20);
    engine->drawBackgroundString(x, 0, "PAUSED", 0xabc09f);
}

void StatePause::mainLoopBeforeUpdate() {
    offset = (offset+1) % engine->getWindowHeight();
    engine->redrawDisplay();
}


void StatePause::copyAllBackgroundBuffer() {
    DrawingSurface *s = engine->getForegroundSurface();
    DrawingSurface *b = engine->getBackgroundSurface();
    int winw = engine->getWindowWidth();
    int winh = engine->getWindowHeight();

    // scrolls the bg
    s->copyRectangleFrom(b, 0,0, winw, winh, 0, offset);
    s->copyRectangleFrom(b, 0, winh - offset, winw, winh, 0, offset- winh);
}


void StatePause::initObjects() {
    //int n = 1;
    engine->createObjectArray(1);

    StateLevel *level = decideLevel();
    level->data = level_data;
    level->fromPause = true;
    UIContinueButton *cb = new UIContinueButton(this, level);
    int x = engine->getWindowWidth()/2 - 100;
    cb->setPosition(x, engine->getWindowHeight()/2 + 10);
    engine->storeObjectInArray(0, cb);
}


