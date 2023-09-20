#pragma once
#include "DisplayableObjectContainer.h"

class BulletContainer : public DisplayableObjectContainer {
public:
    void setHasActed(bool acted = false);

    void drawAllBullets();

    void updateAllBullets(int iCurrentTime);
};
