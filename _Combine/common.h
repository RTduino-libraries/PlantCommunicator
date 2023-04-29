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

/*std header files, this header files cannot export to C++. That's why declear here*/
#include <Adafruit_AHTX0.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <CapacitiveSensor.h>

#ifndef __COMMON_H__
#define __COMMON_H__ 1

/*__cplusplus*/
#ifdef __cplusplus
extern "C"{
#endif

/* This MACRO is optimized for STM32F401 which provides single-precision FPU.*/
#define TO_FAHRENHEIT(celsuis) ((celsuis * 1.8f) + 32.0f)

#define CHECK_SENSOR(data, sensor_name) do { \
    if(!data) { \
        puts(sensor_name "sensor data not available"); \
    } \
} while(0)

void read_htaSensor(void);
void display_oled(volatile float *, volatile float *);
void read_touchSensor(void);
void display_led(int *);
float to_fahrenheit(float celsius);

// Callback methods prototypes
void htaSensor_Callback();
void touchSensor_Callback();

struct ops{
    void (*ptr) (void);
};
typedef struct ops *ops_t;

extern Adafruit_AHTX0 aht;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern CapacitiveSensor capSensor; 
extern ops_t local;

#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
