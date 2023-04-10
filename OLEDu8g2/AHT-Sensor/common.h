/*
 * Copyright (c) 2021-2022, RTduino Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-04-10     Stanley Lwin      first version
 */
#ifndef __COMMON_H__
#define __COMMON_H__

/*__cplusplus*/
#ifdef __cplusplus
extern "C"{
#endif

#define TEMP 0
#define HUMIDITY  10

struct Data{
    float temp;
    float humidity;
};
typedef struct Data data_t;

#ifdef __cplusplus
}
#endif
/*__cplusplus*/
#endif /*__COMMON_H__*/
