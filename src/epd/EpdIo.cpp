/**
 * EpdIo.cpp
 *
 * Convenience functions for communication with the
 * Waveshare 4.2inch e-Paper (B) SPI controller
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */

#include "EpdIo.h"
#include <Arduino.h>
#include <SPI.h>

EpdIo::EpdIo(int pinSDI, int pinSCK, int pinCS,
             int pinDC, int pinRST, int pinBUSY)
    : pinSDI(pinSDI), pinSCK(pinSCK), pinCS(pinCS)
    , pinDC(pinDC), pinRST(pinRST), pinBUSY(pinBUSY) {
}

void EpdIo::init(void) {
    pinMode(pinCS, OUTPUT);
    pinMode(pinRST, OUTPUT);
    pinMode(pinDC, OUTPUT);
    pinMode(pinBUSY, INPUT);

    digitalWrite(pinCS, HIGH);
    digitalWrite(pinRST, LOW);
    digitalWrite(pinDC, LOW);

    SPI.begin(pinSCK, -1, pinSDI, -1);
    SPI.beginTransaction(SPISettings(2000000, MSBFIRST, SPI_MODE0));
}

void EpdIo::reset(void) {
    digitalWrite(pinRST, HIGH);
    delay(200);
    digitalWrite(pinRST, LOW);
    delay(2);
    digitalWrite(pinRST, HIGH);
    delay(200);
}

void EpdIo::setDataMode(bool dataMode) {
    digitalWrite(pinDC, dataMode ? HIGH : LOW);
}

void EpdIo::waitIdle(void) {
    /* pin is inverted, more accurately described as NBUSY */
    while (digitalRead(pinBUSY) == LOW)
        delay(50);
}

void EpdIo::send(uint8_t val) {
    digitalWrite(pinCS, LOW);
    SPI.transfer(val);
    digitalWrite(pinCS, HIGH);
}

void EpdIo::sendCmd(uint8_t cmd) {
    waitIdle();
    setDataMode(false);
    send(cmd);
}

void EpdIo::sendData(uint8_t data) {
    setDataMode(true);
    send(data);
}

void EpdIo::sendData(void *buf, uint32_t size) {
    uint8_t *bbuf = (uint8_t *)buf;
    for (uint32_t i = 0; i < size; i++)
        sendData(bbuf[i]);
}
