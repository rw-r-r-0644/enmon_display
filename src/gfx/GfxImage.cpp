/**
 * GfxImage.cpp
 * Extended image drawing functions
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "GfxImage.h"

GfxImage::GfxImage(const Content &content, Color color)
: GfxImage(content, color, MOD_NONE) {}

GfxImage::GfxImage(const Content &content, Color color, int modifier)
: content(content), color(color), modifier(modifier) {}

GfxImage::GfxImage(const GfxImage &source)
: content(source.content), color(source.color), modifier(source.modifier) {}

GfxImage GfxImage::horizontalFlip(void) const {
    return GfxImage(content, color, modifier ^ MOD_H_FLIP);
}

GfxImage GfxImage::verticalFlip(void) const {
    return GfxImage(content, color, modifier ^ MOD_V_FLIP);
}

void GfxImage::drawPixel(Adafruit_GFX &gfx, int16_t x, int16_t y, int set) const {
    int tx = (modifier & MOD_H_FLIP) ? (content.width - x) : x;
    int ty = (modifier & MOD_V_FLIP) ? (content.height - y) : y;
    GfxColor col = set ? color.fg : color.bg;

    if (col != TRANSPARENT)
      gfx.drawPixel(tx, ty, col);
}

int GfxImage::drawRLEBlock(Adafruit_GFX &gfx, int16_t x, int16_t y, uint8_t block) const {
    if (block & 0x80) { // RLE-encoding block
        int pxSet = (block >> 6) & 1;
        int count = (block & 63) + 1;

        for (int i = 0; i < count; i++)
            drawPixel(gfx, x + i, y, pxSet);

        return count;
    } else { // direct-encoding block
        for (int i = 0; i < 7; i++) {
            block <<= 1;
            drawPixel(gfx, x + i, y, block & 0x80);
        }

        return 7;
    }
}

void GfxImage::draw(Adafruit_GFX &gfx, int16_t x, int16_t y) const {
    gfx.startWrite();

    int offs = 0;
    for (int16_t j = 0; j < content.height; j++)
        for (int16_t i = 0; i < content.width;)
            i += drawRLEBlock(gfx, x+i, y+j, content.data[offs++]);

    gfx.endWrite();
}
