/*
 * handle_leds.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */
#include "handle_leds.h"
int blinkFlag1 = 0;
int blinkFlag2 = 0;

void blinkLEDs(int traffic, int color){
	// set flag for blinking
	if(traffic == TRAFFIC_1){
		blinkFlag1 = 1 - blinkFlag1;
		switch(color){
			case AUTO_RED:
				if(blinkFlag1) Traffic_setColor(1, AUTO_RED);
				else Traffic_setColor(1, OFF_LED);
				break;
			case AUTO_YELLOW:
				if(blinkFlag1) Traffic_setColor(1, AUTO_YELLOW);
				else Traffic_setColor(1, OFF_LED);
				break;
			case AUTO_GREEN:
				if(blinkFlag1) Traffic_setColor(1, AUTO_GREEN);
				else Traffic_setColor(1, OFF_LED);
				break;
			default:
				break;
		}
	}

	else if(traffic == TRAFFIC_2){
		blinkFlag2 = 1 - blinkFlag2;
		switch(color){
			case AUTO_RED:
				if(blinkFlag2) Traffic_setColor(2, AUTO_RED);
				else Traffic_setColor(2, OFF_LED);
				break;
			case AUTO_YELLOW:
				if(blinkFlag2) Traffic_setColor(2, AUTO_YELLOW);
				else Traffic_setColor(2, OFF_LED);
				break;
			case AUTO_GREEN:
				if(blinkFlag2) Traffic_setColor(2, AUTO_GREEN);
				else Traffic_setColor(2, OFF_LED);
				break;
			default:
				break;
		}
	}
}

void Traffic_setColor(int option, int color){
	if(option == 1){
		switch(color){
			case AUTO_RED:
				HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
				HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
				break;
			case AUTO_YELLOW:
				HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, SET);
				HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
				break;
			case AUTO_GREEN:
				HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
				HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, SET);
				break;
			case OFF_LED:
				HAL_GPIO_WritePin(D2_GPIO_Port, D2_Pin, RESET);
				HAL_GPIO_WritePin(D3_GPIO_Port, D3_Pin, RESET);
				break;
			default:
				break;
		}
	}
	else if(option == 2){
		switch(color){
			case AUTO_RED:
				HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
				HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
				break;
			case AUTO_YELLOW:
				HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, SET);
				HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
				break;
			case AUTO_GREEN:
				HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
				HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, SET);
				break;
			case OFF_LED:
				HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, RESET);
				HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, RESET);
				break;
			default:
				break;
		}
	}
}

void Pedestrian_setColor(int color){
	if(color == AUTO_RED){
		// RED LED
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, SET);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);

	}
	else if(color == AUTO_GREEN){
		// GREEN LED
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, RESET);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, SET);

	}
	else if(color == OFF_LED){
		// OFF LED
		HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, RESET);
		HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, RESET);
	}
}

//void updateBuffer(){
//	led_buffer[0] = timerTraffic1 / 10;
//	led_buffer[1] = timerTraffic1 % 10;
//	led_buffer[2] = timerTraffic2 / 10;
//	led_buffer[3] = timerTraffic2 % 10;
//}


