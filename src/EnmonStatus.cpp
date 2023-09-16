/**
 * EnmonStatus.cpp
 * Retrieve update new energy monitor status
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#include "EnmonStatus.h"
#include "Config.h"
#include "utils/WiFiConnection.h"
#include "utils/Json.h"
#include <PubSubClient.h>
#include <WiFi.h>

#define TOPIC_STATUS ("enmon/" CONFIG_ENMON_PLANT_NAME "/status")
#define TOPIC_WEATHER ("enmon/" CONFIG_ENMON_PLANT_NAME "/weather")


/* statically allocate TCP and MQTT client */
static WiFiClient wifiClient;
static PubSubClient mqttClient(wifiClient);


/* saved in RTC, preserved during deep sleep */
static RTC_DATA_ATTR long
lastUpdateTimestamp = 0;


/**
 * Update last enmon status timestamp
 * Returns true if the timestamp changed from
 * the last update
 */
static bool updateStatusTimestamp(const EnmonStatus &status) {
    if (status.timestamp > lastUpdateTimestamp) {
        lastUpdateTimestamp = status.timestamp;
        return true;
    }
    return false;
}


/**
 * Update Energy Monitor status from MQTT
 * Returns true if there's any new information to display
 */
static bool updateFromMqtt(EnmonStatus &status, EnmonWeather &weather) {
    StaticJsonDocument<256> doc;
    bool statusUpdated = false, weatherUpdated = false;

    mqttClient.setServer(CONFIG_MQTT_BROKER, CONFIG_MQTT_BROKER_PORT);

    /* process MQTT messages from subscribed topics*/
    mqttClient.setCallback([&](char* topic, byte* payload, unsigned int length) {
        deserializeJson(doc, payload, length);
        if (!strcmp(topic, TOPIC_STATUS))
            statusUpdated = deserialize(status, doc);
        else if (!strcmp(topic, TOPIC_WEATHER))
            weatherUpdated = deserialize(weather, doc);
    });

    /* connect to MQTT broker */
    if (!mqttClient.connect("enmon-display")) {
        Serial.print("MQTT connection failed! rc = ");
        Serial.println(mqttClient.state());
        return false;
    }
    mqttClient.subscribe(TOPIC_STATUS, 1);
    mqttClient.subscribe(TOPIC_WEATHER, 1);

    /* wait for MQTT messages within 5s */
    int timeout = millis() + 5000;
    while ((millis() < timeout) && !(statusUpdated && weatherUpdated)) {
        mqttClient.loop();
        delay(100);
    }

    /* disconnect */
    mqttClient.setCallback(nullptr);
    mqttClient.disconnect();

    /* check if the new status data is newer than what is currently displayed */
    return statusUpdated
        && updateStatusTimestamp(status);
}


/**
 * Update Energy Monitor status
 * Returns true if there's any new information to display
 */
bool updateEnmon(EnmonStatus &status, EnmonWeather &weather) {
    /* WiFi is costs a lot of battery, deinitialize as soon as possible */
    wifiInit();
    bool result = updateFromMqtt(status, weather);
    wifiEnd();
    return result;
}
