/**
 * EpdIo.h
 *
 * Convenience functions for communication with the
 * Waveshare 4.2inch e-Paper (B) SPI controller
 *
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include <Arduino.h>

class EpdIo {
    int pinSDI, pinSCK, pinCS, pinDC, pinRST, pinBUSY;

    void setDataMode(bool dataMode);
    void waitIdle(void);
    void send(uint8_t val);

public:
    EpdIo(int pinSDI, int pinSCK, int pinCS,
          int pinDC, int pinRST, int pinBUSY);

    void init(void);
    void reset(void);

    void sendCmd(uint8_t cmd);
    void sendData(uint8_t data);
    void sendData(void *buf, uint32_t size);
};
