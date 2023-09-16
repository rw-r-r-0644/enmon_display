/**
 * Json.h
 * Deserializer implementation for ArduinoJson
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#define ARDUINOJSON_DECODE_UNICODE 0
#include <ArduinoJson.h>

class JsonDeserializer {
    const JsonDocument &doc;

public:
    JsonDeserializer(const JsonDocument &doc)
        : doc(doc) {}

    template<typename F>
    bool field(const char *name, F &ref) {
        JsonVariantConst var = doc[name];
        if (!var.is<F>())
            return false;
        ref = var.as<const F>();
        return true;
    }
};

template<typename T>
bool deserialize(T &data, const JsonDocument &doc) {
    JsonDeserializer deserializer(doc);
    return data.deserialize(deserializer);
}
