/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-24     Stanley Lwin      first version
 */

#include "common.h"

Adafruit_AHTX0 aht;

void temp_humi_init(void)
{
    if (!aht.begin())
    {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
     
    Serial.println("AHT10 or AHT20 begin!");
}

float get_temp(void)
{
    sensors_event_t temp;
    aht.getEvent(NULL, &temp);

    CHECK_SENSOR(temp.temperature, "Temperature");

    return TO_FAHRENHEIT(temp.temperature);
}

float get_humi(void)
{
    sensors_event_t humidity;
    aht.getEvent(&humidity, NULL);

    CHECK_SENSOR(humidity.relative_humidity, "Humidity");

    return humidity.relative_humidity;
}
