#include "header.h"
#include "Psymp12Engine.h"

#include "DrawingOutsideWindow.h"
#include "Player.h"
#include "ImageManager.h"

#include "State.h"
#include "StateMenu.h"

Psymp12Engine::Psymp12Engine()
    : game_state(nullptr),
    extra_surface_1(this),
    extra_surface_2(this),
    extra_surface_3(this) {
    //scrolling_filter;
    //game_state = nullptr;
    transitionTo(new StateMenu());
}



void Psymp12Engine::drawGrid(int x, int y) {
    if(y % 16 == 0) {
        setBackgroundPixel(x,y, 0xffff00);
    }
    if(x % 16 == 0) {
        setBackgroundPixel(x,y,0x00ff00); 
    }
}

void Psymp12Engine::virtCleanUp() {
    ImageManager::destroyImageManager();
}



void Psymp12Engine::virtCreateSurfaces() {
    int w = 2124;
    m_oTheBackgroundSurface.createSurface(w, m_iWindowHeight);
    m_oTheForegroundSurface.createSurface(w, m_iWindowHeight);

    printf("width: %d\n", m_iWindowWidth);

    // these get swapped in for the bg
    extra_surface_1.createSurface(w, m_iWindowHeight);
    extra_surface_2.createSurface(w, m_iWindowHeight);
    extra_surface_3.createSurface(w, m_iWindowHeight);


}


void Psymp12Engine::virtSetupBackgroundBuffer() {
    //std::cout << "Setting up background\n";
    virtCleanUp();
    
    fillBackground(0xD16644);
    
    if(state_changed) {
        game_state->drawBG();
        state_changed = false;
    }
    /*
    for(int x=0; x < getWindowWidth(); x++) {
        for(int y=0; y < this->getWindowHeight(); y++) {
            if(x * y < 1000) {
                createCorners(x, y, 0xD16644);
            }
        }
    }
    */
}

void Psymp12Engine::copyAllBackgroundBuffer() {
    game_state->copyAllBackgroundBuffer();
}


int Psymp12Engine::virtInitialise() {
    std::cout << "Initialising everything\n";
    
    // set up background
    //m_pBackgroundSurface->setDrawPointsFilter(&scrolling_filter);
    m_pBackgroundSurface->mySDLLockSurface();
    virtSetupBackgroundBuffer();
    m_pBackgroundSurface->mySDLUnlockSurface();

    //set up extra backgrounds
    extra_surface_1.mySDLLockSurface();
    extra_surface_2.mySDLLockSurface();
    extra_surface_3.mySDLLockSurface();

    // sets up the animation bg
    DrawingOutsideWindow::DrawOnSurface(&extra_surface_1, ImageManager::loadImage("resources/skyspirals1.png"));
    DrawingOutsideWindow::DrawOnSurface(&extra_surface_2, ImageManager::loadImage("resources/skyspirals2.png"));
    DrawingOutsideWindow::DrawOnSurface(&extra_surface_3, ImageManager::loadImage("resources/skyspirals3.png"));

    extra_surface_1.mySDLUnlockSurface();
    extra_surface_2.mySDLUnlockSurface();
    extra_surface_3.mySDLUnlockSurface();
    
    // initialise objects
    virtInitialiseObjects();

    return 0;
}

int Psymp12Engine::virtInitialiseObjects() {
    drawableObjectsChanged();
    destroyOldObjects(true);
    
    game_state->initObjects();
    
    setAllObjectsVisible(true);
    return 0;
}

void Psymp12Engine::drawAllObjects() {
    for (auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++)
        if (*it) 
            (*it)->setHasActed(false);

    bool finished = false;
    while (!finished)
    {
        //std::cout << "starting draw loop..." << std::endl;
        m_bDrawableObjectsChanged = false; // Moved to inside loop to avoid infinite loop
        finished = true;
        for (auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); it++)
        {
            if (*it)
            {
                if (!(*it)->getHasActed())
                {
                    //std::cout << "draw " << (int)(*it) << std::endl;
                    (*it)->setHasActed(true);
                    (*it)->virtDraw();
                }
                if (m_bDrawableObjectsChanged)
                {
                    finished = false;
                    break; // from the for statement - will repeat loop again
                }
            }
        }
    }

    game_state->drawAllTemporaryObjects();
}


void Psymp12Engine::virtDrawStringsOnTop() {
    if (cw_debug) {
        drawDebugText();
    }
}

// adds a cool corner effect, sort of in a fish eyes/CRT style :)
void Psymp12Engine::createCorners(int x, int y, int colour = 0x112233) {
    setBackgroundPixel(x,y, colour);
    setBackgroundPixel(m_iWindowWidth-x-1, y, colour);
    setBackgroundPixel(m_iWindowWidth-x-1, m_iWindowHeight-y-1, colour);
    setBackgroundPixel(x, m_iWindowHeight-y-1, colour);
}

void Psymp12Engine::drawDebugText() {
    const int colour = 0x59abc1;

    char mousePosition[32];
    sprintf_s(mousePosition, "Mouse position: (%d, %d)", getCurrentMouseX(), getCurrentMouseY());

    std::string curState = "state: " + game_state->state_name;
    
    drawForegroundString(50, 50, "DEBUG", colour, NULL);
    drawForegroundString(50, 70, mousePosition, colour, NULL);
    drawForegroundString(50, 90, curState.c_str(), colour, NULL);

    char buf3[120];
    sprintf_s(buf3, "Engine Objects initialised: %d", getContentCount());
    
    drawForegroundString(50, 130, buf3, colour, NULL);

    game_state->debugText();
}

void Psymp12Engine::virtKeyDown(int iKeyCode) {
    currentKey = iKeyCode;
    switch(iKeyCode) {
        case SDLK_ESCAPE:
            //setExitWithCode(0);
            game_state->onPause();
            break;
        case SDLK_r:
            cw_debug = !cw_debug;
            printf("debug is now %s\n", cw_debug ? "true" : "false");
            break;
    } 
}

void Psymp12Engine::virtMainLoopDoBeforeUpdate() {
    // up to the state to change the actual current surface value
    switch (current_surface) {
        case 1:
            m_pBackgroundSurface = &extra_surface_1;
            break;
        case 2:
            m_pBackgroundSurface = &extra_surface_2;
            break;
        case 3:
            m_pBackgroundSurface = &extra_surface_3;
            break;
        default:
            m_pBackgroundSurface = &m_oTheBackgroundSurface;
            break;
    }
    
    game_state->mainLoopBeforeUpdate();
}


void Psymp12Engine::virtMainLoopDoAfterUpdate() {
    game_state->updateAllTemporaryObjects();
}

void Psymp12Engine::virtMainLoopPostUpdate() {
    game_state->mainLoopPostUpdate();
}


void Psymp12Engine::virtMainLoopStartIteration() {
    if(state_changed) {
        lockBackgroundForDrawing();
        virtSetupBackgroundBuffer();
        unlockBackgroundForDrawing();
        virtInitialiseObjects();
    }

    game_state->mainLoopStart();
    
}


void Psymp12Engine::virtPreDraw() {
    game_state->preDrawFG();
}

void Psymp12Engine::virtPostDraw() {
    game_state->postDrawFG();
}
