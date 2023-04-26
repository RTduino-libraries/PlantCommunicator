/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-24     Stanley Lwin      first version
 */

#include <Adafruit_AHTX0.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <CapacitiveSensor.h>
#include "common.h"

#define HTA ( local->ptr = hta)
#define CAP (local->ptr = cap)
#define EXEC (local->ptr())

/*HTA sensor*/
Adafruit_AHTX0 aht;

/*OLED Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

/*Captive Sensor*/
const int writePin = 4;
const int readPin = 2;
const int ledPin = D7;
CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

struct ops plant;
ops_t local  = &plant;

void setup()
{
    Serial.begin(115200);

    /*HTA sensor*/
    Serial.println("Adafruit AHT10/AHT20 demo!");

    if (! aht.begin())
    {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT10 or AHT20 found");

    /*OLED */
    u8g2.begin();

    /*Captive Sensor*/
    digitalWrite(ledPin, LOW);
    capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop()
{

    HTA;EXEC;
    CAP;EXEC;

    delay(15);
}
