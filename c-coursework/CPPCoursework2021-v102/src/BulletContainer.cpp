#include "BulletContainer.h"

void BulletContainer::setHasActed(bool acted) {
    for(auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); ++it) {
        if(*it) {
            (*it)->setHasActed(acted);
        }
    }
}


void BulletContainer::updateAllBullets(int iCurrentTime) {
    setHasActed();

    bool finished = false;
    while(!finished) {
        m_bDrawableObjectsChanged = false;
        finished = true;
        for(auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); ++it) {
            if(*it) {
                if(!(*it)->getHasActed()) {
                    (*it)->setHasActed(true);
                    (*it)->virtDoUpdate(iCurrentTime);
                }
                if(m_bDrawableObjectsChanged) {
                    finished = false;
                    break;
                }
            }
        }
    }
}


void BulletContainer::drawAllBullets() {
    setHasActed();
    bool finished = false;
    while(!finished) {
        m_bDrawableObjectsChanged = false;
        finished = true;

        for(auto it = m_vecDisplayableObjects.begin(); it != m_vecDisplayableObjects.end(); ++it) {
            if(*it) {
                if(!(*it)->getHasActed()) {
                    (*it)->setHasActed(true);
                    (*it)->virtDraw();
                }
                if(m_bDrawableObjectsChanged) {
                    finished = false;
                    break; // from the for statement - will repeat loop again
                }
            }
        }

    }

}
