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

Adafruit_AHTX0 aht;

/*Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

void Weather::drawWeatherSymbol(uint8_t x, uint8_t y, uint8_t symbol)
{
  // fonts used:
  // u8g2_font_open_iconic_weather_4x_t
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
        u8g2.print("�F");        // requires enableUTF8Print()
    else if(symbol == HUMIDITY)
        u8g2.print("%");
}

void Weather::draw(const char *s, uint8_t symbol, float degree)
{
    int16_t offset = -(int16_t)u8g2.getDisplayWidth();
    int16_t len = strlen(s);

    u8g2.clearBuffer();            
    drawWeather(symbol, degree);   

    for(;;)                        
    {
        u8g2.setFont(u8g2_font_fur14_tf);
        u8g2.drawStr(0,58,s);
        u8g2.sendBuffer();

        delay(2);
        offset+=2;
        if ( offset > len*8+1 )
            break;
    }
}

void Weather::newThread(void)
{
        cout << "New Thread Starting" << endl;
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
}

void loop(void)
{
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    Weather _weather(temp.temperature, humidity.relative_humidity);
    _weather.draw("Temperature", TEMP, _weather.getTemp());
    _weather.draw("Humidity", HUMIDITY, _weather.getHumidity());
}


