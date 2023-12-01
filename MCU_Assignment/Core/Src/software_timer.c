#include "software_timer.h"

int timer7SEG = 0;
int counter7SEG = 0;

int timerSecond = 0;
int counterSecond = 0;

int timerFlag[NO_OF_COUNTERS] = {0, 0, 0, 0, 0, 0};
int counter[NO_OF_COUNTERS] = {0, 0, 0, 0, 0, 0};

void setTimer7SEG(int duration){
	counter7SEG = duration/PERIOD;
	timer7SEG = 0;
}

void setTimerSecond(int duration){
	counterSecond = duration/PERIOD;
	timerSecond = 0;
}

void setTimer(int index, int duration){
	counter[index] = duration/PERIOD;
	timerFlag[index] = 0;
}

void timerRun(){
	for (int i = 0; i < NO_OF_COUNTERS; i++){
		if (counter[i] > 0){
			counter[i]--;
			if (counter[i] <= 0){
				timerFlag[i] = 1;
			}
		}
	}
}

void timerRunSecond(){
	if (counterSecond > 0){
		counterSecond--;
		if (counterSecond <= 0){
			timerSecond = 1;
		}
	}
}

void timerRun7SEG(){
	if (counter7SEG > 0){
		counter7SEG--;
		if (counter7SEG <= 0){
			timer7SEG = 1;
		}
	}
}
