/**
 * WiFiConnection.h
 *
 * Simple WiFi connection helpers
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once

/**
 * wifiInit
 *
 * Try to connect to a WiFi network
 * Returns true if successfully
 */
bool wifiInit(void);


/**
 * wifiEnd
 *
 * Disconnect from WiFi and stop modem
 */
void wifiEnd(void);
