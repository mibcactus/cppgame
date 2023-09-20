#include "StateWin.h"

#include "Psymp12Engine.h"
#include "UIButton.h"
#include "UIExitButton.h"

void StateWin::initObjects() {
    engine->destroyOldObjects(true);
    engine->createObjectArray(3);
    StateMenu *menu = new StateMenu();
    menu->setEngine(engine);
    UIButton *menuButton = new UIButton(this, menu, "MENU");
    menuButton->setScreenPosition(100, engine->getWindowHeight()-256);
    engine->storeObjectInArray(0, menuButton);

    UIExitButton *exit_button = new UIExitButton(this, "EXIT");
    exit_button->setScreenPosition(100,   menuButton->getScreenY() + exit_button->getDrawHeight());
    engine->storeObjectInArray(1, exit_button);

    
    UIButton *next_level_button = new UIButton(this, new_level,"NEXT STAGE");
    next_level_button->setScreenPosition(100, exit_button->getScreenY() + next_level_button->getDrawHeight());
    engine->storeObjectInArray(2, next_level_button);
}


void StateWin::drawBG() {
    SimpleImage bg = ImageManager::loadImage("resources/daysky.png");
    bg.renderImage(engine->getBackgroundSurface(), 0,0,0,0, bg.getWidth(), bg.getHeight());

    int x, y;
    SimpleImage win = ImageManager::loadImage("resources/stage cleared.png");
    x = engine->getWindowWidth()/2 - win.getWidth()/2;
    win.renderImageWithMask(engine->getBackgroundSurface(), 0,0, x,20, win.getWidth(), win.getHeight());

    unsigned int colour = 0xb5819e;
    engine->drawBackgroundRectangle(150, 400, engine->getWindowWidth()-140, 520, colour);

    int x2 = 200;
    engine->drawBackgroundString(x2, 420, "You've vanquished all of the foes! Unfortunately, it", 0);
    engine->drawBackgroundString(x2, 440, "     seems their leader has yet to be defeated.", 0);
    engine->drawBackgroundString(x2, 460, "You decide to head onwards, curious as to what", 0);
    engine->drawBackgroundString(x2, 480, "    mysterious lands and beasts you'll face.", 0);
}

