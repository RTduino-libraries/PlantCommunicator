/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-24     Stanley Lwin      first version
 */
#ifndef __COMMON_H__
#define __COMMON_H__

/*__cplusplus*/
#ifdef __cplusplus
extern "C"{
#endif

/*Captive Sensor*/
const int writePin = 4;
const int readPin = 2;
const int ledPin = D7;
CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

/*LED pin*/
int ledB = D3;
int ledR = D6;
int ledG = D5;
int brightness = 0;
int fadeAmount = 5;

/*OLED Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

/*HTA sensor*/
Adafruit_AHTX0 aht;

struct ops{
    void (*ptr) (void);
};
typedef struct ops *ops_t;

struct ops plantC;
ops_t local  = &plantC;

void hta(void);
void oled(volatile float *, volatile float *);
void cap(void);
void led(int *);

#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
