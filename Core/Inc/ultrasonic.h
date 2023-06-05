/*
 * ultrasonic.h
 *
 *  Created on: Aug 2, 2022
 *      Author: Lenovo
 */

#ifndef INC_ULTRASONIC_H_
#define INC_ULTRASONIC_H_

#include "stm32l4xx_hal.h"

void ultrasonic_init(void);
uint16_t Get_distance(void);
extern uint8_t g_dataReady_u8;

#endif /* INC_ULTRASONIC_H_ */
