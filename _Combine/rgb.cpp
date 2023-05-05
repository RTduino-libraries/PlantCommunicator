/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-24     Stanley Lwin      first version
 * Next step to refactor the code by Mecto to professional code. ^@^
 */

#include "common.h"

/*LED pin*/
int ledB = D3;
int ledR = D6;
int ledG = D5;
int brightness = 0;
int fadeAmount = 5;

void rgb_init(void)
{
    rt_kprintf("RGB begin!");
}

void set_rgb(volatile int ledVal)
{
    analogWrite(ledB, 5 - ledVal); 
    analogWrite(ledR, 10 - ledVal);
    analogWrite(ledG, 12 - ledVal);

    brightness = brightness + fadeAmount;

    if (brightness <= 0 || brightness >= 255)
    {
        fadeAmount = -fadeAmount;
    }
}
