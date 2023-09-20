#include "StateMenu.h"

#include "Psymp12Engine.h"
#include "StateCredits.h"
#include "StateLevel_0.h"
#include "UIButton.h"
#include "UIExitButton.h"


void StateMenu::drawBG() {
    std::string bgURL = "resources/bg1.png";
    engine->bg = ImageManager::get()->getImagebyURL(bgURL,true, true);
    //engine->bg.renderImage(engine->getBackgroundSurface(), 0,0,0,0,engine->bg.getWidth(), engine->bg.getHeight());
    DrawingSurface *temp = engine->getBackgroundSurface();
    engine->bg.renderImage(
        temp,
        0,0,
        0,0,
        engine->bg.getWidth(), engine->bg.getHeight());
}

void StateMenu::initObjects() {
    int n = 3;
    engine->createObjectArray(n);

    StateLevel *level = new StateLevel_0();
    level->setEngine(engine);
    
    UIButton *playButton = new UIButton(this, level, "PLAY");
    playButton->initialiseAllPositions(100, engine->getWindowHeight()-256);
    engine->storeObjectInArray(0, playButton);


    StateCredits *credits = new StateCredits();
    credits->setEngine(engine);
    
    UIButton *creditsButton = new UIButton(this, credits, "CREDITS");
    creditsButton->initialiseAllPositions(100, playButton->getScreenY() + creditsButton->getDrawHeight());
    engine->storeObjectInArray(1, creditsButton);
    
    
    UIExitButton *exit_button = new UIExitButton(this, "EXIT");
    exit_button->initialiseAllPositions(100,   creditsButton->getScreenY() + exit_button->getDrawHeight());
    engine->storeObjectInArray(2, exit_button);
}


