#include "StateLevel_2.h"

#include "Psymp12Engine.h"
#include "StateWin.h"


void StateLevel_2::allMobsDead() {



    //State *win = new State
    engine->state_changed = true;
    engine->transitionTo(new StateEnd);
}
