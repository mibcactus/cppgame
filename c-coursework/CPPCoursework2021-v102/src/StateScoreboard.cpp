#include "StateScoreboard.h"

#include "Psymp12Engine.h"
#include "StateMenu.h"
#include "UIButton.h"


void StateScoreboard::drawBG() {
    engine->fillBackground(0xABCDEF);
    int x = 0, y = 0;
    for (x = 0; x < engine->getWindowWidth(); x++){
        for (y = 0; y < engine->getWindowHeight(); y++){
            switch (rand() % 100){
                case 0: engine->setBackgroundPixel(x, y, 0xFF0000); break;
                case 1: engine->setBackgroundPixel(x, y, 0x00FF00); break;
                case 2: engine->setBackgroundPixel(x, y, 0x0000FF); break;
                case 3: engine->setBackgroundPixel(x, y, 0xFFFF00); break;
                case 4: engine->setBackgroundPixel(x, y, 0x00FFFF); break;
                case 5: engine->setBackgroundPixel(x, y, 0xFF00FF); break;
            }
        }
    }
    std::string text = "2023";
    unsigned int colour = 0x23ae69;
    engine->drawBackgroundString(100,50, text.c_str(), colour, NULL);
}

void StateScoreboard::initObjects() {
    // menu button
    engine->createObjectArray(1);
    StateMenu *menu = new StateMenu();
    menu->setEngine(engine);
    UIButton *menuButton = new UIButton(this, menu, "MENU");
    menuButton->setScreenPosition(100, engine->getWindowHeight()-256);
    engine->storeObjectInArray(0, menuButton);
}


