/**
 * EnmonGUI.h
 * Update display GUI with the provided data
 * 
 * Copyright (C) 2023 rw-r-r-0644
 * This file is under MIT license
 */
#pragma once
#include "EnmonStatus.h"


/**
 * updateGUI
 *
 * Update display with the given energy
 * monitor status and weather data
 */
void updateGUI(const EnmonStatus &status, const EnmonWeather &weather);
