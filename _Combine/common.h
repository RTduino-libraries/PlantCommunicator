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

#define ERR 0
#define OK 1

#define TO_FAHRENHEIT(celsuis) ((celsuis * 1.8f) + 32.0f)

#define CHECK_SENSOR(data, sensor_name) do { \
    if(!data) { \
        puts(sensor_name "sensor data not available"); \
        sensor_error = ERR; \
    } \
    sensor_error = OK; \
} while(0)

/*AHT sensor prototypes*/
void temp_humi_init(void);
float get_temp(void);
float get_humi(void);

/*Capacitive Sensor prototypes*/
void capac_init(void);
int get_capac(void);

/*OLED prototypes*/
void oled_init(void);
void display_oled(volatile float, volatile float);

/*RGB prototype*/
void rgb_init(void);
void set_rgb(volatile int);

/*Interface*/
struct ops{
    void (*ptr) (void);
};
typedef struct ops *ops_t;

extern Adafruit_AHTX0 aht;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern CapacitiveSensor capSensor;
extern ops_t local;
extern int sensor_error;

#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
