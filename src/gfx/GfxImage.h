/**
 * GfxImage.h
 * Extended image drawing functions
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Adafruit_GFX.h>
#include "GfxTypes.h"

class GfxImage {
public:
    struct Content {
        int16_t width, height;
        const uint8_t *data;
        Content(int16_t width, int16_t height, const uint8_t data[])
        : width(width), height(height), data(data) {}
    };
    struct Color {
        GfxColor fg, bg;
        Color(GfxColor fg, GfxColor bg) : fg(fg), bg(bg) {}
    };

    GfxImage(const Content &content, Color color = Color(BLACK, TRANSPARENT));
    GfxImage(const GfxImage &source);

    GfxImage horizontalFlip(void) const;
    GfxImage verticalFlip(void) const;

    void draw(Adafruit_GFX &gfx, int16_t x, int16_t y) const;

private:
    const Content content;
    const Color color;
    enum {
        MOD_NONE   = 0,
        MOD_H_FLIP = 1 << 0,
        MOD_V_FLIP = 1 << 1,
    };
    const int modifier;

    GfxImage(const Content &content, Color color, int modifier);
    void drawPixel(Adafruit_GFX &gfx, int16_t x, int16_t y, int set) const;
    int drawRLEBlock(Adafruit_GFX &gfx, int16_t x, int16_t y, uint8_t block) const;
};
