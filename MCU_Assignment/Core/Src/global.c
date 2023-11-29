/*
 * global.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */


#include "global.h"

int status = INIT;

int timerTraffic1 = 0;
int timerTraffic2 = 0;

int durationRED = 5000;
int durationYELLOW = 2000;
int durationGREEN = 3000;

int led_index = 0;
int led_buffer[4] = {0};

int buzzer_value = 0;
int index_buzzer = 1;
