/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-12     Stanley Lwin      first version
 */

#include <Adafruit_AHTX0.h>
#include <rtthread.h>
#include <Arduino.h>
/* no capable of using in multi-thread environment */
#include <U8g2lib.h>
#include "common.h"
/*Capacitive Sensor*/
#include <CapacitiveSensor.h>
CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

Adafruit_AHTX0 aht;
sensors_event_t humidity, temp;

Weather _weather(temp.temperature, humidity.relative_humidity);

/*Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

void Weather::drawWeatherSymbol(uint8_t x, uint8_t y, uint8_t symbol)
{
  // fonts used:
  // u8g2_font_open_iconic_embedded_6x_t
  // u8g2_font_open_iconic_weather_6x_t
  // encoding values, see: https://github.com/olikraus/u8g2/wiki/fntgrpiconic

    switch(symbol)
    {
        case TEMP:
            u8g2.setFont(u8g2_font_open_iconic_weather_4x_t);
            u8g2.drawGlyph(x, y, 65);
            break;
        case HUMIDITY:
            u8g2.setFont(u8g2_font_open_iconic_thing_4x_t);
            u8g2.drawGlyph(x, y, 72);
            break;
    }
}

void Weather::drawWeather(uint8_t symbol, float degree)
{
    /* x, y */
    int feh;
    feh = (degree * 9 / 5 ) + 32;
    drawWeatherSymbol(0, 35, symbol);
    u8g2.setFont(u8g2_font_logisoso32_tf);
    u8g2.setCursor(48+3, 38);
    u8g2.print(feh);
    if(symbol == TEMP)
        u8g2.print("°F");        // requires enableUTF8Print()
    else if(symbol == HUMIDITY)
        u8g2.print("%");
}

void Weather::draw(const char *s, uint8_t symbol, float degree)
{
    int16_t offset = -(int16_t)u8g2.getDisplayWidth();
    int16_t len = strlen(s);

    u8g2.clearBuffer();                // clear the internal memory
    drawWeather(symbol, degree);      // draw the icon and degree only once
    for(;;)                           // then do the scrolling
    {
        u8g2.setFont(u8g2_font_fur14_tf);
        u8g2.drawStr(0,58,s);
        u8g2.sendBuffer();              // transfer internal memory to the display

        delay(2);
        offset+=2;
        if ( offset > len*8+1 )
            break;
    }
}

void Weather::newThread(void)
{
       rt_kprintf("Starting a new thread\n");
       tid = rt_thread_create("thread", _weather.thread_entry, RT_NULL, THREAD_STACK_SIZE, THREAD_PRIORITY, THREAD_TIMESLICE);

         if(tid != RT_NULL)
         {
             rt_thread_startup(tid);
         }
         else
         {
             rt_thread_delete(tid);
         }
}

/*Entry function for tid1*/
void Weather:: thread_entry(void *parameter)
{
    digitalWrite(ledPin, HIGH);
    capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);

    while(1)
    {
        long sensorValue = capSensor.capacitiveSensor(30);
        Serial.println(sensorValue);

        /*map(value, fromLow, fromHigh, toLow, toHigh)*/
        LedVal = map(sensorValue, 0, 1023, 0, 255);

        analogWrite(ledR, LedVal - brightness ); // digital using PWM

        delay(30);
    }
}

float Weather::getTemp(void)
{
    return temp;
}

float Weather::getHumidity(void)
{
    return humidity;
}

void setup(void)
{
    aht.begin();
    u8g2.begin();
    u8g2.enableUTF8Print();


    if (! aht.begin()) {
      Serial.println("Could not find AHT? Check wiring");
      while (1) delay(10);
    }
    Serial.println("AHT10 or AHT20 found");
    _weather.newThread();
}

void loop(void)
{

    aht.getEvent(&humidity, &temp);

    _weather.draw("Temperature", TEMP, _weather.getTemp());
    _weather.draw("Humidity", HUMIDITY, _weather.getHumidity());
}


