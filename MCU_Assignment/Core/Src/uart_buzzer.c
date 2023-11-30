/*
 * uart_buzzer.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */
#include "uart_buzzer.h"

void buzzer(){
	// Implement buzzer here...
	__HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, buzzer_value);
}
