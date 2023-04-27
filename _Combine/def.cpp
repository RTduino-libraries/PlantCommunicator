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

/*LED pin*/
int ledB = D3;
int ledR = D6;
int ledG = D5;
int brightness = 0;
int fadeAmount = 5;

/*Sensor Group One */
void hta(void)
{
    sensors_event_t humidity, temp;
    volatile float tempL, humidityL;

    aht.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data

    tempL = TO_FAHRENHEIT(temp.temperature);
    humidityL = humidity.temperature;
    Serial.print("Temperature: "); Serial.print(tempL); Serial.println(" degrees F");
    Serial.print("Humidity: "); Serial.print(humidityL); Serial.println("% rH");

    oled(&tempL, &humidityL);
}

void oled(volatile float *temp, volatile float *humidity)
{
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_helvB10_tr);   // choose a suitable font

    u8g2.drawStr(1,20,"Temp:");    // write something to the internal memory
    u8g2.setCursor(75, 20); // x,y
    u8g2.drawStr(115,20,"F");
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
