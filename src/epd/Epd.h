/**
 * Epd.h
 *
 * Waveshare 4.2inch e-Paper (B) library,
 * with Adafruit GFX support
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Adafruit_GFX.h>
#include "EpdIo.h"

#define EPDC_WHITE           0b11
#define EPDC_BLACK           0b10
    #define EPDC_BLACK_PLANE(c)    ((c) & 1)
#define EPDC_RED             0b01
    #define EPDC_RED_PLANE(c)      ((c) >> 1)

class Epd : public Adafruit_GFX {
    GFXcanvas1 blackCanvas, redCanvas;
    EpdIo io;

    void frameUpdate(uint8_t *frame, int color);
    void refreshDisplay(void);

public:
    static const unsigned
        WIDTH = 400,
        HEIGHT = 300;

    /* constructor */
    Epd(int pinSDI, int pinSCK, int pinCS,
        int pinDC, int pinRST, int pinBUSY);

    /* display functions */
    void init(void);        // init (or wakeup) display
    void sleep(void);       // enter deep sleep
    void display(void);     // update screen from canvas

    /* Adafruit GFX functions */
    void drawPixel(int16_t x, int16_t y, uint16_t color) override;
    void fillScreen(uint16_t color) override;
    void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
};
