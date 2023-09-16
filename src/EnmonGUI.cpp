/**
 * EnmonGUI.cpp
 * Update display GUI with the provided data
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "EnmonGUI.h"
#include "Config.h"
#include "resources/Images.h"
#include "resources/FreeMonoBold10pt7b.h"
#include "epd/Epd.h"
#include <stdarg.h>

/**
 * Statically allocated EDP driver
 */
static Epd gfx(CONFIG_PIN_EPD_SDI, CONFIG_PIN_EPD_SCK, CONFIG_PIN_EPD_CS,
    CONFIG_PIN_EPD_DC, CONFIG_PIN_EPD_RST, CONFIG_PIN_EPD_BUSY);


/**
 * Print formatted text centered horizontally
 */
static void printfCenter(int cx, int y, const char *fmt, ...) {
    va_list va;
    char buf[128];
    
    va_start(va, fmt);
    vsnprintf(buf, sizeof(buf), fmt, va);
    va_end(va);

    uint16_t w, h; int16_t x1, y1;
    gfx.getTextBounds(buf, 0, gfx.height() - 1, &x1, &y1, &w, &h);
    gfx.setCursor(cx - w / 2, y + h / 2);
    gfx.print(buf);
}


/**
 * Draw weather conditions
 */
static void drawWeather(const EnmonWeather &weather) {
    static GfxImageBWR const * const conditions[] = {
        &img_weather_0, &img_weather_1, &img_weather_2,
        &img_weather_3, &img_weather_4, &img_weather_5
    };

    if (weather.code >= 0 && weather.code < sizeof(conditions) / sizeof(*conditions)) {
        conditions[weather.code]->draw(gfx, 320, 50);
        printfCenter(345, 111, "%dC", weather.temperature);
    }
}


/**
 * Draw battery icon, flows and percentage
 */
static void drawBattery(char percentage_battery) {
    if (percentage_battery < 0)
        return;

    img_battery.draw(gfx, 96, 15);
    for (int i = 0; i < 4 && percentage_battery > 25*i; i++)
        gfx.fillRect(237, 67 - 10*i, 22, 7, EPDC_RED);
    printfCenter(248, 97, "%d%%", percentage_battery);
}


/**
 * Draw power flow textbox
 */
static void drawPowerTextBox(int x, int y, int watts) {
    gfx.fillRect(x, y, 76, 26, EPDC_WHITE);
    gfx.drawRect(x, y, 76, 26, EPDC_BLACK);
    printfCenter(x+38, y+13, "%dW", watts);
}


/**
 * Draw all power flows and arrows
 */
static void drawPowerInformation(const EnmonStatus &status) {
    img_background.draw(gfx, 0, 0);
    printfCenter(58, 97, "%dW", status.meter_generation);

    int home_consumption = status.meter_generation
        + status.meter_battery + status.meter_grid;
    printfCenter(248, 273, "%dW", home_consumption);

    int generation_to_battery = 0, battery_to_home = 0;
    if (status.meter_battery > 0) {
        battery_to_home = status.meter_battery;
        drawPowerTextBox(210, 138, battery_to_home);
        img_flow_vert.draw(gfx, 242, 122);
    } else if (status.meter_battery < 0) {
        generation_to_battery = -status.meter_battery;
        drawPowerTextBox(115, 52, generation_to_battery);
        img_flow_horiz.draw(gfx, 100, 60);
    }

    int generation_to_grid = 0, grid_to_home = 0; 
    if (status.meter_grid > 0) {
        grid_to_home = status.meter_grid;
        drawPowerTextBox(115, 225, grid_to_home);
        img_flow_horiz.draw(gfx, 100, 230);
    } else if (status.meter_grid < 0) {
        generation_to_grid = -status.meter_grid;
        drawPowerTextBox(20, 138, generation_to_grid);
        img_flow_vert.draw(gfx, 52, 122);
    }

    int generation_to_home = status.meter_generation
        - generation_to_battery - generation_to_grid;
    if (generation_to_home > 0) {
        drawPowerTextBox(115, 138, generation_to_home);
        img_flow_diag.draw(gfx, 103, 105);
    }
}


/**
 * Draw update time
 */
static void drawUpdateTime(const EnmonStatus &status) {
    struct tm update_time;

    time_t utc_timestamp = status.timestamp;
    localtime_r(&utc_timestamp, &update_time);
    
    printfCenter(345, 241, "%02d:%02d",
        update_time.tm_hour, update_time.tm_min);
}


/**
 * Update display with the given energy
 * monitor status and weather data
 */
void updateGUI(const EnmonStatus &status, const EnmonWeather &weather) {
    gfx.init();
    gfx.fillScreen(EPDC_WHITE);
    gfx.setFont(&FreeMonoBold10pt7b);
    gfx.setTextColor(EPDC_BLACK);

    drawBattery(status.percentage_battery);
    drawPowerInformation(status);
    drawWeather(weather);
    drawUpdateTime(status);

    gfx.display();
    gfx.sleep();
}
