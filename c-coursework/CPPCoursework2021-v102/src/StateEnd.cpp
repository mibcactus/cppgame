#include "StateEnd.h"

#include "Psymp12Engine.h"
#include "StateCredits.h"
#include "UIExitButton.h"


void StateEnd::drawBG() {
    bg.renderImage(engine->getBackgroundSurface(),0,0,0,0, bg.getWidth(), bg.getHeight());
    congrats.renderImageWithMask(engine->getBackgroundSurface(), 0,0,0,0, congrats.getWidth(), congrats.getHeight());
}

void StateEnd::initObjects() {
    engine->createObjectArray(2);
    UIExitButton *exit_button = new UIExitButton(this, "EXIT");
    exit_button->initialiseAllPositions(100, 850);
    engine->storeObjectInArray(0, exit_button);

    StateCredits *credits = new StateCredits();
    credits->setEngine(engine);
    UIButton *creditsButton = new UIButton(this, credits, "CREDITS");
    creditsButton->initialiseAllPositions(100, 800);
    engine->storeObjectInArray(1, creditsButton);
}

