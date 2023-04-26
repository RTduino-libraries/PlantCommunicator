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
#ifndef __COMMON_H__
#define __COMMON_H__

/*__cplusplus*/
#ifdef __cplusplus
extern "C"{
#endif

void hta(void);
void oled(volatile float *, volatile float *);
void cap(void);
void led(int *);

struct ops{
    void (*ptr) (void);
};
typedef struct ops *ops_t;

extern Adafruit_AHTX0 aht;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern CapacitiveSensor capSensor; //CapacitiveSensor capSensor = CapacitiveSensor(writePin,readPin);
extern ops_t local;

#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
