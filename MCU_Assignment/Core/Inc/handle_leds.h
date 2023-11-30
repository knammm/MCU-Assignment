/*
 * handle_leds.h
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */

#ifndef INC_HANDLE_LEDS_H_
#define INC_HANDLE_LEDS_H_

#include "global.h"

extern int blinkFlag1;
extern int blinkFlag2;
void clear7SEGs();
void clearEN();
void blinkLEDs(int, int);
void Traffic_setColor(int, int);
void Pedestrian_setColor(int);
void display7SEG(int);
void update7SEG();
void updateBuffer();


#endif /* INC_HANDLE_LEDS_H_ */
