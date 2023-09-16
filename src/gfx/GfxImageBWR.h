/**
 * GfxImageBWR.h
 * Convenience wrapper to draw B/W/R images
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Adafruit_GFX.h>
#include "GfxImage.h"
#include "GfxTypes.h"

class GfxImageBWR {
public:
    struct Content {
        int16_t width, height;
        const uint8_t *blackData;
        const uint8_t *redData;
        Content(int16_t width, int16_t height, const uint8_t blackData[], const uint8_t redData[])
        : width(width), height(height), blackData(blackData), redData(redData) {}
    };

    GfxImageBWR(const Content &content, GfxColor bgColor = TRANSPARENT);
    GfxImageBWR(const GfxImageBWR &source);

    GfxImageBWR horizontalFlip(void) const;
    GfxImageBWR verticalFlip(void) const;

    void draw(Adafruit_GFX &gfx, int16_t x, int16_t y) const;

private:
    GfxImageBWR(GfxImage black, GfxImage red);

    const GfxImage black, red;
};
