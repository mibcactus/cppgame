#include "Entity.h"

#include "Animation.h"
#include "BaseEngine.h"

void Entity::updateAnimationHook(int time) {
    anim->updateFrame(time); // the player dying can cause an access violation when trying to set this
}

Entity::~Entity() {
    //printf("Entity destroyed.\n");
    if(anim) {
        delete anim;
    }
}

int Entity::getLocalXfromSurfaceX(int surface_x) {
    if(anim != nullptr) {
        return surface_x - position_x + anim->getCurrentFrame().spritesheet_x;
    }
    return surface_x - position_x;
}


int Entity::getLocalYfromSurfaceY(int surface_y) {
    if(anim != nullptr) {
        return surface_y - position_y + anim->getCurrentFrame().spritesheet_y;
    }
    return surface_y - position_y;
}


int Entity::getPixel(int x, int y) {
    if(anim) {
        int sheet_x = x + anim->getCurrentFrame().spritesheet_x;
        int sheet_y = y + anim->getCurrentFrame().spritesheet_y;
    
        return anim->spritesheet.getPixelColour(sheet_x, sheet_y);
    }
    return texture.getPixelColour(x, y);
}

void Entity::virtDraw() {
    if(anim) {
        anim->drawCurrentFrame();
    } else {
        getEngine()->drawForegroundRectangle(
            getScreenX(), getScreenY(),
            m_iCurrentScreenX + m_iDrawWidth - 1,
            m_iCurrentScreenY + m_iDrawHeight - 1,
            colour);
    }
}

void Entity::checkBoundaries() {
    
    if(position_x < 0) {
        position_x = 0;
    } else if (position_x >= getEngine()->getBackgroundSurface()->getSurfaceWidth() - m_iDrawWidth) {
        position_x = getEngine()->getBackgroundSurface()->getSurfaceWidth() - m_iDrawWidth;
    }

    if(position_y < 0) {
        position_y = 0;
    } else if (position_y >= getEngine()->getBackgroundSurface()->getSurfaceHeight() - m_iDrawHeight) {
        position_y = getEngine()->getBackgroundSurface()->getSurfaceHeight() - m_iDrawHeight;
    }
    
}

