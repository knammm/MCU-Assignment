/*
 * fsm_pedestrian.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */
#include "fsm_pedestrian.h"

int pedestrianFlag = 0;
int pedestrianStatus = INIT;
int speed[5] = {400, 300, 200, 100, 50};
int indexForSpeed = 0;

// Function to handle the buzzer process
void buzzerProcess(int value) {
    buzzer_value = value;
    buzzer();
}

void fsm_pedestrian_run() {
    int needMore = 5 - (durationYELLOW / 1000);
    switch (pedestrianStatus) {
        case INIT:
            buzzerProcess(0);
            indexForSpeed = 0;
            setTimer(3, 10);
            setTimer(4, 10);
            Pedestrian_setColor(OFF_LED);
			// Change status
            if (pedestrianFlag == 1) {
                if (status == RED_GREEN || status == RED_YELLOW) {
                    pedestrianStatus = AUTO_GREEN;
                } else if (status == YELLOW_RED || status == GREEN_RED) {
                    pedestrianStatus = AUTO_RED;
                }
                pedestrianFlag = 0; // Make sure to restart the flag
            }
            break;

        case AUTO_GREEN:
            Pedestrian_setColor(AUTO_GREEN);
			// Change status
            if (timerFlag[2] == 1) pedestrianStatus = INIT;
            else if (status == YELLOW_RED || status == GREEN_RED) pedestrianStatus = AUTO_RED;
			/*
				Buzzer processing...
				Two case: Yellow is longer than initial duration (5), Yellow is less than...
				Initial frequency : 128
			*/
            if (durationYELLOW < 5000) {
                if (status == RED_GREEN && timerTraffic2 <= needMore) {
					// Calculate the appropriate index
                    indexForSpeed = needMore - timerTraffic2;
                    if (timerFlag[3] == 1) {
                        buzzerProcess(512 * (1 + indexForSpeed));
                        setTimer(3, speed[indexForSpeed]); // Set the speed through array
                        setTimer(4, 20); // Set delay for turn off buzzer
                    }

                    if (timerFlag[4]==1){
                    	buzzerProcess(0);
                    }

                } else if (status == RED_YELLOW) {
					// In this status, just care about "timerTraffic2"
                    if (timerFlag[3] == 1) {
                        buzzerProcess(512 * (5 - timerTraffic2 + 1));
                        setTimer(3, speed[5 - timerTraffic2]);
                        setTimer(4, 20);
                    }
                    if (timerFlag[4] == 1) {
                        buzzerProcess(0);
                    }
                }
            } else if (durationYELLOW >= 5000 && status == RED_YELLOW && timerTraffic2 <= 5) {
				// The code is the same as above RED_YELLOW
                if (timerFlag[3] == 1) {
                    buzzerProcess(512 * (5 - timerTraffic2 + 1));
                    setTimer(3, speed[5 - timerTraffic2]);
                    setTimer(4, 20);
                }
                if (timerFlag[4] == 1) {
                    buzzerProcess(0);
                }
            }
            break;

        case AUTO_RED:
            buzzerProcess(0);
            indexForSpeed = 0;
            setTimer(3, 10);
            setTimer(4, 10);
            Pedestrian_setColor(AUTO_RED);

            if (timerFlag[2] == 1) {
                pedestrianStatus = INIT;
            } else if (status == RED_GREEN || status == RED_YELLOW) {
                pedestrianStatus = AUTO_GREEN;
            }
            break;

        default:
            break;
    }
}
