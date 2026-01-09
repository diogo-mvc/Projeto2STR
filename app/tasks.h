#ifndef APP_TASKS_H
#define APP_TASKS_H



#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h" /*for semaphores and such*/

#include "../drivers/clock.h"
#include "display.h"
#include "helper/monitor.h" /*read user I2C communication*/

// Macros for task stack sizes and priorities
#define SENSOR_TASK_STACK_SIZE      256
#define SENSOR_TASK_PRIORITY        2

#define BUBBLE_LEVEL_TASK_STACK_SIZE 256
#define BUBBLE_LEVEL_TASK_PRIORITY   2

#define DISPLAY_TASK_STACK_SIZE     256
#define DISPLAY_TASK_PRIORITY       2

#define USER_INTERFACE_TASK_STACK_SIZE 256
#define USER_INTERFACE_TASK_PRIORITY   1

#define ALARM_TASK_STACK_SIZE      256
#define ALARM_TASK_PRIORITY        2

#define BUZZER_TASK_STACK_SIZE 256
#define BUZZER_TASK_PRIORITY    2

#define HITBIT_TASK_STACK_SIZE 256
#define HITBIT_TASK_PRIORITY    2


#ifdef __cplusplus
extern "C" {
#endif

// Initialize all application tasks
void app_tasks_init(void);

// Example task function prototypes
void vSensorTask(void *pvParameters);
void vBubbleLevelTask(void *pvParameters);
void vDisplayTask(void *pvParameters);
void vUserInterfaceTask(void *pvParameters);
void vAlarmTask(void *pvParameters);
void vBuzzerTask(void *pvParameters);
void vHitBitTask(void *pvParameters);

// Hit Bit game initialization
void hitbit_init(void);

#ifdef __cplusplus
}
#endif

#endif // APP_TASKS_H
