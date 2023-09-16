/**
 * GfxImageBWR.cpp
 * Convenience wrapper to draw B/W/R images
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include "GfxImageBWR.h"

GfxImageBWR::GfxImageBWR(const Content &content, GfxColor bgColor)
: black(GfxImage::Content(content.width, content.height, content.blackData),
    GfxImage::Color(BLACK, bgColor))
, red(GfxImage::Content(content.width, content.height, content.redData),
    GfxImage::Color(RED, TRANSPARENT))
{}

GfxImageBWR::GfxImageBWR(const GfxImageBWR &source)
: black(source.black), red(source.red) {}

GfxImageBWR::GfxImageBWR(GfxImage black, GfxImage red)
: black(black), red(red) {}

GfxImageBWR GfxImageBWR::horizontalFlip(void) const {
    return GfxImageBWR(black.horizontalFlip(), red.horizontalFlip());
}

GfxImageBWR GfxImageBWR::verticalFlip(void) const {
    return GfxImageBWR(black.verticalFlip(), red.verticalFlip());
}

void GfxImageBWR::draw(Adafruit_GFX &gfx, int16_t x, int16_t y) const {
    black.draw(gfx, x, y);
    red.draw(gfx, x, y);
}
