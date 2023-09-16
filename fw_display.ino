#include "src/Config.h"
#include "src/EnmonStatus.h"
#include "src/EnmonGUI.h"

void setup() {
    EnmonStatus status;
    EnmonWeather weather;
  
    setenv("TZ", CONFIG_TIMEZONE, 1);
    tzset();
  
    if (updateEnmon(status, weather))
        updateGUI(status, weather);
  
    /* enter deep sleep */
    esp_sleep_enable_timer_wakeup(
        CONFIG_UPDATE_INTERVAL * 1000000ULL);
    esp_deep_sleep_start();
}

void loop() {}
