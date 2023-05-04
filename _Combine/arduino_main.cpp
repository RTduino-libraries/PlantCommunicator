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

#define HTA ( local->ptr = read_htaSensor)
#define TOUCH (local->ptr = read_touchSensor)
#define EXEC (local->ptr())

/*HTA sensor*/
Adafruit_AHTX0 aht;

/*OLED Default Constructor*/
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2 (U8G2_R0, U8X8_PIN_NONE, U8X8_PIN_NONE, U8X8_PIN_NONE);

/*Captive Sensor*/
const int writePin = 4;
const int readPin = 2;
const int ledPin = D7;
CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);

/*func pointer structure*/
struct ops plant;
ops_t local  = &plant;

/*Task Scheduler Obj*/
Scheduler runner;

//Tasks
Task htaSensor(2000, TASK_FOREVER, &htaSensor_Callback);
Task touchSensor(3000, TASK_FOREVER, &touchSensor_Callback);

// error handling
volatile int sensor_error = 0;

//to track the sensor available
bool sensor_available = true;

void setup()
{
    Serial.begin(115200);

    /*HTA sensor*/
    Serial.println("Plant Communication Demo App");

    if (!aht.begin())
    {
        Serial.println("Could not find AHT? Check wiring");
        while (1) delay(10);
    }
    Serial.println("AHT10 or AHT20 begin: ");

    /*OLED */
    if(!u8g2.begin())
    {
        Serial.println("Could not find Oled? Check wiring");
    }
    Serial.println("u8g2 sensor begin !");
    /*Captive Sensor*/
    digitalWrite(ledPin, LOW);
    capSensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
    Serial.println("capative sensor begin");

    /*Task Scheduler*/
    runner.init();
    runner.addTask(htaSensor);
    runner.addTask(touchSensor);
    htaSensor.enable();
    touchSensor.enable();
    Serial.println("task scheduler begin");
}

void loop()
{
    runner.execute();
    delay(1);
}

void htaSensor_Callback() {
    Serial.println("################HTA Sensor################");
    HTA;EXEC;
    htaSensor.setInterval(50);
}

void touchSensor_Callback()
{
    Serial.println("################Touch Sensor################");
    TOUCH;EXEC;
    touchSensor.setInterval(500);
}

