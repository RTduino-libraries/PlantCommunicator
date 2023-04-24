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
#include "U8x8lib.h"
#include <CapacitiveSensor.h>
#include "common.h"

#define EXEC (local->ptr())

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
    /*func pointer mapping*/
    local->ptr = hta;
    EXEC;
    local->ptr = cap;
    EXEC;

    delay(15);
}

/*Sensor Group One */
void hta(void)
{
    sensors_event_t humidity, temp;
    volatile float tempL, humidityL;

    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

    tempL = temp.temperature;
    humidityL = humidity.temperature;
    Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
    Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

    oled(&tempL, &humidityL);
}

void oled(volatile float *temp, volatile float *humidity)
{
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_helvB10_tr);   // choose a suitable font

    u8g2.drawStr(1,20,"Temp");    // write something to the internal memory
    u8g2.setCursor(75, 20); // x,y
    u8g2.drawStr(115,20,"C");
    u8g2.print(*temp);

    u8g2.drawStr(1,50,"Humidity");
    u8g2.setCursor(75, 50); // x,y
    u8g2.print(*humidity);
    u8g2.drawStr(115,50,"%");

    u8g2.sendBuffer();
}

/*Sensor Group Two */
void cap(void)
{
    long sensorValue = capSensor.capacitiveSensor(30);
    int ledVal;

    ledVal = map(sensorValue, 0, 2500, 0, 255);
    Serial.print("Captive: "); Serial.println(sensorValue);
    led(&ledVal);
}

void led(int *ledVal)
{
    analogWrite(ledB, 5 - *ledVal); //this is digital using PWM
    analogWrite(ledR, 10 - *ledVal);
    analogWrite(ledG, 12 - *ledVal);

    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;

    }
}


