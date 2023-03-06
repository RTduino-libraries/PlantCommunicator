/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2023-03-05     Stanley Lwin    first version
 */

#include <Arduino.h>
#include <U8g2lib.h>
#include "U8x8lib.h"

/*Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

void setup(void) 
{
    u8g2.begin();
}

void loop(void) 
{
    u8g2.clearBuffer();                   // clear the internal memory
    u8g2.setFont(u8g2_font_ncenB08_tr);   // choose a suitable font
    u8g2.drawStr(0,10,"Hello World!");    // write something to the internal memory
    u8g2.sendBuffer();                    // transfer internal memory to the display
    delay(1000);
}
