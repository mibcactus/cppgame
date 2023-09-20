#include "StateLose.h"

#include "Psymp12Engine.h"
#include "UIButton.h"
#include "UIExitButton.h"

void StateLose::drawBG() {
    engine->fillBackground(0x00000);
    /*
    engine->drawBackgroundString(
        engine->getWindowWidth()/2,
        // ReSharper disable once CppCStyleCast
        (int) floor(engine->getWindowHeight() * 0.66),
        "YOU DIED", 0xFFFF00);*/
    SimpleImage img = ImageManager::loadImage("resources/you died.png");
    //img.renderImageWithMask(engine->getForegroundSurface(), 0,0,400,400,img.getWidth(), img.getHeight(), img.getPixelColour(0,0));
    img.renderImageWithMask(engine->getBackgroundSurface(),
        0,0,
        0,0,
        engine->getWindowWidth(), engine->getWindowHeight(),
        img.getPixelColour(0,0));
}

void StateLose::postDrawFG() {
    

}


void StateLose::initObjects() {
    engine->createObjectArray(2);
    
    UIExitButton *exit_button = new UIExitButton(this, "QUIT");
    exit_button->setScreenPosition(200, 800);
    engine->storeObjectInArray(0, exit_button);

    UIButton *menuButton = new UIButton(this, new StateMenu, "MENU");
    menuButton->setScreenPosition(200 + exit_button->getDrawWidth() + 10, 800);
    engine->storeObjectInArray(1, menuButton);
}
