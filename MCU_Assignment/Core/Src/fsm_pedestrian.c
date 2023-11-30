/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */
#include "fsm_pedestrian.h"

int pedestrianFlag = 0;
int pedestrianStatus = INIT;
int flagBuzzer = 0;
int timerBuzzer = 500;
int timerMinus = 50;

// Function to handle the buzzer process
void buzzerProcess(int value) {
    buzzer_value = value;
    buzzer();
}

void fsm_pedestrian_run() {
    switch (pedestrianStatus) {
        case INIT:
            // Initialization phase
            buzzerProcess(0);
            flagBuzzer = 0;
            timerBuzzer = 500;
            setTimer(3, 10);
            Pedestrian_setColor(OFF_LED);

            // Check for pedestrian signal
            if (pedestrianFlag == 1) {
                // Transition to AUTO_GREEN or AUTO_RED based on traffic signal
                if (status == RED_GREEN || status == RED_YELLOW) {
                    pedestrianStatus = AUTO_GREEN;
                } else if (status == YELLOW_RED || status == GREEN_RED) {
                    pedestrianStatus = AUTO_RED;
                }
                pedestrianFlag = 0;  // Reset pedestrian flag
            }
            break;

        case AUTO_GREEN:
            // Automatic mode with green signal for pedestrians
            Pedestrian_setColor(AUTO_GREEN);

            // Check for conditions to transition back to INIT
            if (timerFlag[2] == 1){
            	pedestrianStatus = INIT;
            }
            else if(status == YELLOW_RED || status == GREEN_RED) {
                pedestrianStatus = AUTO_RED;
            }

            // Buzzer process during green signal with specific conditions
            if (durationYELLOW < 5000) {
                int needMore = 5 - (durationYELLOW / 1000);
                if((timerTraffic2 <= needMore && status == RED_GREEN) || status == RED_YELLOW) flagBuzzer = 1;
                if(timerFlag[3] == 1){
                	timerBuzzer = timerBuzzer - timerMinus;
                	if(timerBuzzer <= 150)  timerBuzzer = 150;
                	if(status == RED_YELLOW && timerTraffic2 <= 2) timerBuzzer = 100;
                	if(flagBuzzer) buzzerProcess(32 * (6 - (durationYELLOW / 1000) - timerTraffic2));
                	HAL_Delay(10);
                	setTimer(3, timerBuzzer);

                }
                else buzzerProcess(0);
                // Execute buzzer process if needed
            } else if (durationYELLOW >= 5000 && status == RED_YELLOW && timerTraffic2 <= 5) {
                // Buzzer process during specific conditions in red-yellow transition
                if(timerFlag[3] == 1){
                	timerBuzzer = timerBuzzer - timerMinus;
                	if(timerBuzzer <= 100) timerBuzzer = 100;
                	buzzerProcess(32 * (6 - timerTraffic2));
                	// Give a delay...
                	HAL_Delay(10);
                	setTimer(3, timerBuzzer);

                }
                else buzzerProcess(0);
            }
            // Buzzer for duration yellow < 5
            break;

        case AUTO_RED:
            // Automatic mode with red signal for pedestrians
            buzzerProcess(0);
            flagBuzzer = 0;
            timerBuzzer = 500;
            setTimer(3, 10);
            Pedestrian_setColor(AUTO_RED);

            // Check for conditions to transition back to INIT
            if (timerFlag[2] == 1 ){
            	pedestrianStatus = INIT;
            }
            else if(status == RED_GREEN || status == RED_YELLOW) {
                pedestrianStatus = AUTO_GREEN;
            }
            break;

        default:
            break;
    }
}
