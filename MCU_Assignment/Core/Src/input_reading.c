/*
 * input_reading.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */
#include <input_reading.h>

static GPIO_PinState buttonBuffer[NO_OF_BUTTONS] = {BUTTON_IS_RELEASED};
static GPIO_PinState debounceButtonBuffer1[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer2[NO_OF_BUTTONS];
static GPIO_PinState debounceButtonBuffer3[NO_OF_BUTTONS];

int buttonFlag[NO_OF_BUTTONS] = {0};
int buttonTimeOut[NO_OF_BUTTONS] = {0};

uint16_t pins[NO_OF_BUTTONS] = {A0_Pin, A1_Pin, A2_Pin, A3_Pin};
GPIO_TypeDef* ports[NO_OF_BUTTONS] = {A0_GPIO_Port, A1_GPIO_Port, A2_GPIO_Port, A3_GPIO_Port};

void button_reading(){
	for(int i = 0; i < NO_OF_BUTTONS; i++){
		debounceButtonBuffer3[i] = debounceButtonBuffer2[i];
		debounceButtonBuffer2[i] = debounceButtonBuffer1[i];
		debounceButtonBuffer1[i] = HAL_GPIO_ReadPin(ports[i], pins[i]);
		if((debounceButtonBuffer3[i] == debounceButtonBuffer2[i]) && (debounceButtonBuffer2[i] == debounceButtonBuffer1[i])){
			if(debounceButtonBuffer1[i] != buttonBuffer[i]){
				buttonBuffer[i] = debounceButtonBuffer1[i];
				if(buttonBuffer[i] == BUTTON_IS_PRESSED){
					buttonFlag[i] = 1;
					buttonTimeOut[i] = 100;
				}
			}
			else{
				buttonTimeOut[i]--;
				if(buttonTimeOut[i] <= 0){
					buttonBuffer[i] = BUTTON_IS_RELEASED;
				}
			}
		}
	}
}

int isButtonPressed(int button_index){
	if(button_index >= NO_OF_BUTTONS || button_index < 0) return 0;
	if(buttonFlag[button_index] == 1){
		buttonFlag[button_index] = 0;
		return 1;
	}
	return 0;
}

void setBackButtonFlag(int index){
	buttonFlag[index] = 1;
}

