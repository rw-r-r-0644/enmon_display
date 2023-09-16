/**
 * Epd.cpp
 *
 * Waveshare 4.2inch e-Paper (B) library,
 * with Adafruit GFX support
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#include <Arduino.h>
#include "Epd.h"
#include "EpdCmd.h"
#include "EpdIo.h"

Epd::Epd(int pinSDI, int pinSCK, int pinCS,
         int pinDC, int pinRST, int pinBUSY)
    : Adafruit_GFX(WIDTH, HEIGHT)
    , blackCanvas(WIDTH, HEIGHT)
    , redCanvas(WIDTH, HEIGHT)
    , io(pinSDI, pinSCK, pinCS, pinDC, pinRST, pinBUSY)
{
}

/* display functions */
void Epd::init(void) {
    io.init();
    io.reset();

    io.sendCmd(CMD_PON);

    io.sendCmd(CMD_PSR);
    io.sendData(PSR_UD | PSR_SHL | PSR_SHD_N | PSR_RST_N);
}

void Epd::sleep() {
    io.sendCmd(CMD_CDI);
    io.sendData(CDI_VBD(3) | CDI_DDX(3) | CDI_CDI(7));

    io.sendCmd(CMD_POF);

    io.sendCmd(CMD_DSLP);
    io.sendData(DSLP_CHECK_MAGIC);
}

void Epd::frameUpdate(uint8_t *frame, int color) {
    io.sendCmd(color == EPDC_BLACK ? CMD_DTM1 : CMD_DTM2);
    delay(2);

    io.sendData(frame, (WIDTH / 8) * HEIGHT);
    delay(2);
}

void Epd::refreshDisplay(void) {
    io.sendCmd(CMD_DRF);
    delay(100);
}

void Epd::display(void) {
    frameUpdate(blackCanvas.getBuffer(), EPDC_BLACK);
    frameUpdate(redCanvas.getBuffer(), EPDC_RED);
    refreshDisplay();
}

/* Adafruit GFX functions */
void Epd::drawPixel(int16_t x, int16_t y, uint16_t color) {
    blackCanvas.drawPixel(x, y, EPDC_BLACK_PLANE(color));
    redCanvas.drawPixel(x, y, EPDC_RED_PLANE(color));
}

void Epd::fillScreen(uint16_t color) {
    blackCanvas.fillScreen(EPDC_BLACK_PLANE(color));
    redCanvas.fillScreen(EPDC_RED_PLANE(color));
}

void Epd::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
    blackCanvas.drawFastVLine(x, y, h, EPDC_BLACK_PLANE(color));
    redCanvas.drawFastVLine(x, y, h, EPDC_RED_PLANE(color));
}

void Epd::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) {
    blackCanvas.drawFastHLine(x, y, w, EPDC_BLACK_PLANE(color));
    redCanvas.drawFastHLine(x, y, w, EPDC_RED_PLANE(color));
}
