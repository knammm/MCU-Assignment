/*
 * global.h
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include "input_reading.h"
#include "main.h"
#include "software_timer.h"
#include "handle_leds.h"
#include "fsm_automatic.h"
#include "fsm_manual.h"
#include "fsm_pedestrian.h"
#include "uart_buzzer.h"

#define INIT		1
#define AUTO_RED    2
#define AUTO_GREEN  3
#define AUTO_YELLOW 4
#define OFF_LED 	5

#define TRAFFIC_1	7
#define TRAFFIC_2	8

#define MOD_RED		11
#define MOD_YELLOW	12
#define MOD_GREEN	13

#define NORMAL		10
#define ADD			15
#define SET			16

#define RED_GREEN 	21
#define RED_YELLOW 	22
#define GREEN_RED 	23
#define YELLOW_RED 	24

extern int status;

extern int timerTraffic1;
extern int timerTraffic2;

extern int durationRED;
extern int durationYELLOW;
extern int durationGREEN;

extern int RED_sec;
extern int YELLOW_sec;
extern int GREEN_sec;

extern int led_index;
extern int led_buffer[4];

extern int index_buzzer;
extern int buzzer_value;

extern TIM_HandleTypeDef htim3;

#endif /* INC_GLOBAL_H_ */
