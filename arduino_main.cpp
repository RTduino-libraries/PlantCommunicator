/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-03-01     Stanley Lwin      first version
 */

#include <Arduino.h>
#include <CapacitiveSensor.h>

const int writePin = 4;
const int readPin = 2;
const int ledPin = D7;


CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

void setup(void)
{
    Serial.begin();
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop(void)
{
   long sensorValue = capSensor.capacitiveSensor(30);

   Serial.println(sensorValue);

   if (sensorValue > 300 )
   {
       digitalWrite(ledPin, HIGH);
   }
   else
   {
       digitalWrite(ledPin, LOW);

   }
   delay(30);
}


