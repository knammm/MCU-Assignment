/*
 * fsm_automatic.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */

#include "fsm_automatic.h"

void fsm_automatic_run(){
	char str[50];
	switch(status){
	case INIT:
		//TODO
		status = RED_GREEN;
		setTimer(0, durationGREEN);
		setTimerSecond(1000);
		break;
	case RED_GREEN:
		//TODO
		Traffic_setColor(1, OFF_LED);
		Traffic_setColor(2, OFF_LED);
		Traffic_setColor(1, AUTO_RED);
		Traffic_setColor(2, AUTO_GREEN);
		if (timerSecond == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG1: %d#\r\n",timerTraffic1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG2: %d#\r\n\n\n",timerTraffic2), 500);
			setTimerSecond(1000);
			timerTraffic1--;
			timerTraffic2--;
			if (timerTraffic2 <= 0) timerTraffic2 = durationYELLOW / 1000;
		}
		// State update
		if (timerFlag[0] == 1){
			setTimer(0, durationYELLOW);
			status = RED_YELLOW;
		}
		break;
	case RED_YELLOW:
		//TODO
		Traffic_setColor(1, OFF_LED);
		Traffic_setColor(2, OFF_LED);
		Traffic_setColor(1, AUTO_RED);
		Traffic_setColor(2, AUTO_YELLOW);
		if (timerSecond == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG1: %d#\r\n",timerTraffic1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG2: %d#\r\n\n\n",timerTraffic2), 500);
			setTimerSecond(1000);
			timerTraffic1--;
			if (timerTraffic1 <= 0) timerTraffic1 = durationGREEN / 1000;
			timerTraffic2--;
			if (timerTraffic2 <= 0) timerTraffic2 = durationRED / 1000;
		}
		// State update
		if(timerFlag[0] == 1){
			setTimer(0, durationGREEN);
			status = GREEN_RED;
		}
		break;
	case GREEN_RED:
		Traffic_setColor(1, OFF_LED);
		Traffic_setColor(2, OFF_LED);
		Traffic_setColor(1, AUTO_GREEN);
		Traffic_setColor(2, AUTO_RED);
		if (timerSecond == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG1: %d#\r\n",timerTraffic1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG2: %d#\r\n\n\n",timerTraffic2), 500);
			setTimerSecond(1000);
			timerTraffic1--;
			if (timerTraffic1 <= 0) timerTraffic1 = durationYELLOW / 1000;
			timerTraffic2--;
		}
		// State update
		if(timerFlag[0] == 1){
			setTimer(0, durationYELLOW);
			status = YELLOW_RED;
		}
		break;
	case YELLOW_RED:
		Traffic_setColor(1, OFF_LED);
		Traffic_setColor(2, OFF_LED);
		Traffic_setColor(1, AUTO_YELLOW);
		Traffic_setColor(2, AUTO_RED);
		if (timerSecond == 1){
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG1: %d#\r\n",timerTraffic1), 500);
			HAL_UART_Transmit(&huart2, (void *)str, sprintf(str, "\r\n!7SEG2: %d#\r\n\n\n",timerTraffic2), 500);
			setTimerSecond(1000);
			timerTraffic1--;
			if (timerTraffic1 <= 0) timerTraffic1 = durationRED / 1000;
			timerTraffic2--;
			if (timerTraffic2 <= 0) timerTraffic2 = durationGREEN / 1000;
		}
		// State update
		if (timerFlag[0] == 1){
			setTimer(0, durationGREEN);
			status = RED_GREEN;
		}
		break;
	default:
		break;
	}
	// MODE BUTTON
	if(isButtonPressed(1) == 1){
		if(status == RED_GREEN || status == RED_YELLOW || status == GREEN_RED || status == YELLOW_RED){
			status = MOD_RED;
			setTimer(1, 10); // timer for blinky
			setTimer(5, 5000);
			Traffic_setColor(1, AUTO_RED);
			Traffic_setColor(2, AUTO_RED);
			RED_sec = durationRED / 1000;
			YELLOW_sec = durationYELLOW / 1000;
			GREEN_sec = durationGREEN / 1000;
			timerTraffic1 = RED_sec;
			timerTraffic2 = 2;
		}
		else setBackButtonFlag(1);
	}
	// PEDESTRIAN BUTTON
	else if(isButtonPressed(0) == 1){
		pedestrianFlag = 1;
		// Set timer for off pedestrian light...
		setTimer(2, 10000); // 10 secs
		setTimer(3, 100);
		setTimer(4, 100);
	}

}
