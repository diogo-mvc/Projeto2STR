#ifndef APP_TASKS_H
#define APP_TASKS_H



#include "FreeRTOS.h"
#include "task.h"


#include "display.h"
#include "helper/monitor.h" /*read user I2C communication*/


// Macros for task stack sizes and priorities
#define SENSOR_TASK_STACK_SIZE      256
#define SENSOR_TASK_PRIORITY        2

#define BUBBLE_LEVEL_TASK_STACK_SIZE 256
#define BUBBLE_LEVEL_TASK_PRIORITY   2

#define RTC_TASK_STACK_SIZE         256
#define RTC_TASK_PRIORITY           2

#define DISPLAY_TASK_STACK_SIZE     256
#define DISPLAY_TASK_PRIORITY       2

#define USER_INTERFACE_TASK_STACK_SIZE 256
#define USER_INTERFACE_TASK_PRIORITY   1 /*low priority, let the kernel switch*/


#ifdef __cplusplus
extern "C" {
#endif

// Initialize all application tasks
void app_tasks_init(void);

// Example: Task function prototypes
void vSensorTask(void *pvParameters);
void vBubbleLevelTask(void *pvParameters);
void vRTCTask(void *pvParameters);
void vDisplayTask(void *pvParameters);
void vUserInterfaceTask(void *pvParameters);

#ifdef __cplusplus
}
#endif

#endif // APP_TASKS_H
