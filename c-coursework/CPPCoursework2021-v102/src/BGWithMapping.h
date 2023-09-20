#pragma once
#include "ImagePixelMapping.h"
#include "Psymp12Engine.h"

class BGWithMapping {
public:
    BGWithMapping(Psymp12Engine* e, SimpleImage t) {
        engine = e;
        bg = t;
    }

    ~BGWithMapping();

    void drawBackgroundTexture(int x_offset) {
        bg.renderImageApplyingMapping(engine, engine->getBackgroundSurface(), x_offset, 0, bg.getWidth(),
                                      bg.getHeight(), new ImagePixelMappingShiftXY(x_offset, 0));

    }

    SimpleImage bg;
    Psymp12Engine* engine;
};
