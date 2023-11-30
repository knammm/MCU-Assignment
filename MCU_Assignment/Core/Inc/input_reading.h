/*
 * input_reading.h
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */

#ifndef INC_INPUT_READING_H_
#define INC_INPUT_READING_H_

#include "main.h"
#include "global.h"

#define NO_OF_BUTTONS		4
#define BUTTON_IS_RELEASED	GPIO_PIN_SET
#define BUTTON_IS_PRESSED	GPIO_PIN_RESET

void button_reading();
int isButtonPressed(int);
void setBackButtonFlag(int);


#endif /* INC_INPUT_READING_H_ */
