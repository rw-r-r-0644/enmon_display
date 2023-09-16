/**
 * WiFiConnection.h
 *
 * Simple WiFi connection helpers
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "WiFiConnection.h"
#include <WiFi.h>
#include "../Config.h"


/**
 * Try to connect to a WiFi network
 * Returns true if successfully
 */
bool wifiInit(void) {
    WiFi.mode(WIFI_STA);
    WiFi.setHostname("enmon-display");
    WiFi.begin(CONFIG_WIFI_SSID, CONFIG_WIFI_PASS);

    const int poll_freq = 100;
    int timeout = CONFIG_WIFI_TIMEOUT * (1000 / poll_freq);

    while ((WiFi.status() != WL_CONNECTED) && (timeout-- > 0))
        delay(poll_freq);

    return timeout > 0;
}


/**
 * Disconnect from WiFi and stop modem
 */
void wifiEnd(void) {
    WiFi.disconnect();
    WiFi.mode(WIFI_OFF);
}
