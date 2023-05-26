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

const int writePin = 4;
const int readPin = 2;
const int ledPin = D7;
static CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

void capac_init(void)
{
    digitalWrite(ledPin, LOW);
    capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
    Serial.println("Capative sensor begin");
}

int get_capac(void)
{
    long sensorValue = capSensor.capacitiveSensor(30);
    register volatile int ledVal = 0;

    ledVal = map(sensorValue, 0, 2500, 0, 255);

    return ledVal;
}
