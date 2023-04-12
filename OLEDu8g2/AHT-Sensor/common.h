/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-12     Stanley Lwin      first version
 */
#ifndef __COMMON_H__
#define __COMMON_H__

/*__cplusplus*/
#ifdef __cplusplus
extern "C"{
#endif

#define TEMP 0
#define HUMIDITY  10

class Weather{
    public:
            Weather(float t, float h)
            {
                temp = t;
                humidity = h;

                newThread();
            }
            void drawWeatherSymbol(uint8_t x, uint8_t y, uint8_t symbol);
            void drawWeather(uint8_t symbol, float degree);
            void draw(const char *s, uint8_t symbol, float degree);
            void newThread();
            float getHumidity();
            float getTemp();

    private:
            float temp;
            float humidity;
};
#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
