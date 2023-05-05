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
#include <TaskScheduler/TaskScheduler.h>

#define HTA_INIT ( local->ptr = temp_humi_init)
#define CAPAC_INIT (local->ptr = capac_init)
#define OLED_INIT (local->ptr = oled_init)
#define RGB_INIT (local->ptr = rgb_init)
#define TASK_INIT (local->ptr = task_init)
#define EXEC (local->ptr())

/*OLED Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

/*func pointer structure*/
struct ops plant;
ops_t local  = &plant;

/*Task Scheduler Obj*/
Scheduler runner;

//Tasks
Task htaSensor(2000, TASK_FOREVER, &htaSensor_Callback);
Task touchSensor(3000, TASK_FOREVER, &touchSensor_Callback);

// error handling
int sensor_error = 0;

//to track the sensor available
bool sensor_available = true;

void setup()
{
    Serial.begin(115200);
    Serial.println("Plant Communication Demo App");

    /*INIT SERVICES*/
    HTA_INIT; EXEC;
    CAPAC_INIT; EXEC;
    OLED_INIT; EXEC;
    RGB_INIT; EXEC;
    TASK_INIT; EXEC;
}

void loop()
{
    runner.execute();
    delay(1);
}

void task_init(void)
{
    runner.init();
    runner.addTask(htaSensor);
    runner.addTask(touchSensor);
    htaSensor.enable();
    touchSensor.enable();
    Serial.println("task scheduler begin");
}

void oled_init(void)
{
    /*OLED */
    if(!u8g2.begin())
    {
        Serial.println("Could not find Oled? Check wiring");
    }
       Serial.println("u8g2 sensor begin !");
}

void display_oled(volatile float temp, volatile float humidity)
{
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_helvB10_tr);

    u8g2.drawStr(1,20,"Temp:");
    u8g2.setCursor(75, 20); // x,y
    u8g2.drawStr(115,20,"F");
    u8g2.print(temp);

    u8g2.drawStr(1,50,"Humidity");
    u8g2.setCursor(75, 50); // x,y
    u8g2.print(humidity);
    u8g2.drawStr(115,50,"%");

    u8g2.sendBuffer();
}

void htaSensor_Callback()
{
    display_oled(get_temp(), get_humi());
    htaSensor.setInterval(50);
}

void touchSensor_Callback()
{
    set_rgb(get_capac());
    touchSensor.setInterval(500);
}

