/*
 * scheduler.c
 *
 *  Created on: Nov 29, 2023
 *      Author: olkmphy
 */

#include "scheduler.h"

typedef struct {
	void ( * pTask)(void);
	uint32_t Delay;
	uint32_t Period;
	uint8_t RunMe;
	uint32_t TaskID;
} sTask;

// The array of tasks
static sTask SCH_tasks_Array[SCH_MAX_TASKS];
static uint32_t newTaskID = 0;


static uint32_t Get_New_Task_ID(void);


void SCH_Init(void){
    for (int i=0; i<SCH_MAX_TASKS; i++){
        SCH_tasks_Array[i].pTask = 0;
        SCH_tasks_Array[i].Delay = 0;
        SCH_tasks_Array[i].Period = 0;
        SCH_tasks_Array[i].RunMe = 0;

        SCH_tasks_Array[i].TaskID = -1;
    }
}

void SCH_Update(){
	if (SCH_tasks_Array[0].pTask && SCH_tasks_Array[0].RunMe == 0) {
		if(SCH_tasks_Array[0].Delay > 0){
			SCH_tasks_Array[0].Delay = SCH_tasks_Array[0].Delay - 1;
		}
		if (SCH_tasks_Array[0].Delay == 0) {
			SCH_tasks_Array[0].RunMe = 1;
		}
	}
}

void SCH_Add_Task(void (*pFunction)(), uint32_t DELAY, uint32_t PERIOD) {
    uint8_t newTaskIndex = 0;
    uint32_t sumDelay = 0;
    uint32_t newDelay = 0;

    // Iterate through the task array to find the appropriate position for the new task
    for (newTaskIndex = 0; newTaskIndex < SCH_MAX_TASKS; newTaskIndex++) {
        // Calculate the cumulative delay of existing tasks
        sumDelay += SCH_tasks_Array[newTaskIndex].Delay;

        // Check if the cumulative delay is greater than the specified initial delay (DELAY)
        if (sumDelay > DELAY) {
            // Calculate the new delay for the current task
            newDelay = DELAY - (sumDelay - SCH_tasks_Array[newTaskIndex].Delay);

            // Adjust the delay of the current task and shift existing tasks to make room
            SCH_tasks_Array[newTaskIndex].Delay = sumDelay - DELAY;
            for (uint8_t i = SCH_MAX_TASKS - 1; i > newTaskIndex; i--) {
                SCH_tasks_Array[i] = SCH_tasks_Array[i - 1];
            }

            // Add the new task at the appropriate position in the array
            SCH_tasks_Array[newTaskIndex] = (sTask){
                .pTask = pFunction,
                .Delay = newDelay,
                .Period = PERIOD,
                .RunMe = (newDelay == 0),  // Set RunMe flag based on newDelay
                .TaskID = Get_New_Task_ID(),  // Assign a unique TaskID
            };

            return;
        } else {
            // If the current task slot is empty, add the new task to this slot
            if (SCH_tasks_Array[newTaskIndex].pTask == 0) {
                SCH_tasks_Array[newTaskIndex] = (sTask){
                    .pTask = pFunction,
                    .Delay = DELAY - sumDelay,
                    .Period = PERIOD,
                    .RunMe = (DELAY - sumDelay == 0),  // Set RunMe flag based on remaining delay
                    .TaskID = Get_New_Task_ID(),  // Assign a unique TaskID
                };

                return;
            }
        }
    }
}



void SCH_Delete_Task(uint32_t taskID) {
    // Check if the provided task ID is NO_TASK_ID (invalid).
    if (taskID == NO_TASK_ID) return;

    // Iterate through the task array to find the task with the specified TaskID
    for (uint8_t taskIndex = 0; taskIndex < SCH_MAX_TASKS; taskIndex++) {
        if (SCH_tasks_Array[taskIndex].TaskID == taskID) {
            // Task found, proceed with deletion

            // If the current task is not the last one and the next task is not empty,
            // adjust the delay of the next task to include the delay of the deleted task.
            if (taskIndex < SCH_MAX_TASKS - 1 && SCH_tasks_Array[taskIndex + 1].pTask != 0) {
                SCH_tasks_Array[taskIndex + 1].Delay += SCH_tasks_Array[taskIndex].Delay;
            }

            // Shift the remaining tasks to fill the gap created by the deleted task
            for (uint8_t j = taskIndex; j < SCH_MAX_TASKS - 1; j++) {
                SCH_tasks_Array[j] = SCH_tasks_Array[j + 1];
            }

            // Clear the last task slot to ensure no leftover data
            SCH_tasks_Array[SCH_MAX_TASKS - 1] = (sTask){0};

            return;
        }
    }

    return; // Task ID not found, exit the function
}


void SCH_Dispatch_Tasks(){
	if(SCH_tasks_Array[0].RunMe > 0) {
		(*SCH_tasks_Array[0].pTask)(); // Function pointer -> Run task
		SCH_tasks_Array[0].RunMe = 0; // Set back RunMe flag
		sTask temtask = SCH_tasks_Array[0];
		SCH_Delete_Task(temtask.TaskID);
		if (temtask.Period != 0) {
			SCH_Add_Task(temtask.pTask, temtask.Period, temtask.Period);
		}
	}
}

static uint32_t Get_New_Task_ID() {
    return ++newTaskID;
}
