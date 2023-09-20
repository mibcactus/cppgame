#include "StateCredits.h"

#include "Bullet.h"
#include "FGDetail.h"
#include "Goober.h"
#include "Psymp12Engine.h"
#include "Psymp12ImagePixelMapping.h"
#include "StateMenu.h"
#include "UIButton.h"

void StateCredits::drawBG() {
    int colour = 0x003399;
    char me[] = "Milica";
    int x = engine->getWindowWidth()/2 + 200;
    bg_texture.renderImage(engine->getBackgroundSurface(),0,0,0,0, bg_texture.getWidth(), bg_texture.getHeight());
    engine->drawBackgroundString(x, 180, "CODING", colour);
    engine->drawBackgroundString(x, 200, me, colour);
    engine->drawBackgroundString(x, 220, "GRAPHICS", colour);
    engine->drawBackgroundString(x, 240, me, colour);
    engine->drawBackgroundString(x, 260, "ENGINE", colour);
    engine->drawBackgroundString(x, 280, "Jason", colour);
    engine->drawBackgroundString(x, 310, "Thank you for playing!", colour);
}

void StateCredits::initObjects() {
    engine->createObjectArray(3);
    StateMenu *menu = new StateMenu();
    menu->setEngine(engine);
    UIButton *menuButton = new UIButton(this, menu, "MENU");
    menuButton->setScreenPosition(100, engine->getWindowHeight()-256);
    engine->storeObjectInArray(1, menuButton);
}

