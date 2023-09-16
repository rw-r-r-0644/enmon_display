/**
 * EnmonStatus.h
 * Retrieve update new energy monitor status
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once

struct EnmonStatus {
    long long timestamp;
    int meter_battery;
    int meter_generation;
    int meter_grid;
    int percentage_battery;

    template <typename Deserializer>
    bool deserialize(Deserializer &d) {
        if (!d.field("meter_battery", meter_battery) ||
            !d.field("percentage_battery", percentage_battery)) {
            meter_battery = 0;
            percentage_battery = -1;
        }
        return d.field("timestamp", timestamp)
            && d.field("meter_generation", meter_generation)
            && d.field("meter_grid", meter_grid);
    }
};

struct EnmonWeather {
    enum Condition {
        WEATHER_UNKNOWN = -1,
        WEATHER_SUN,
        WEATHER_FEW_CLOUDS,
        WEATHER_CLOUDS,
        WEATHER_RAIN,
        WEATHER_THUNDERSTORM,
        WEATHER_NIGHT,

        WEATHER_CONDITION_COUNT,
    };
    
    int code = WEATHER_UNKNOWN;
    int temperature;

    template <typename Deserializer>
    bool deserialize(Deserializer &d) {
        return d.field("code", code)
            && d.field("temperature", temperature);
        /* tag field ignored */
    }
};

/**
 * updateEnmon
 *
 * Update Energy Monitor status
 * Returns true if there's any new information to display
 */
bool updateEnmon(EnmonStatus &status, EnmonWeather &weather);
