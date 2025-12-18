#include "tasks.h"


// Example task handles (if you want to keep references)
TaskHandle_t xSensorTaskHandle        = NULL;
TaskHandle_t xBubbleLevelTaskHandle   = NULL;
TaskHandle_t xRTCTaskHandle           = NULL;
TaskHandle_t xDisplayTaskHandle       = NULL;
TaskHandle_t xUserInterfaceTaskHandle = NULL;

// Task implementations
void vSensorTask(void *pvParameters) {
    for (;;) {
        // Read sensor, process data
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vBubbleLevelTask(void *pvParameters) {
    for (;;) {
        // Update bubble level display
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

void vRTCTask(void *pvParameters) {
    for (;;) {
        // Update RTC
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void vDisplayTask(void *pvParameters) {

    display_init();
    for (;;) {
        
        display_print_screen(12, 34, 56, true, false, 23.5f, 5);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void vUserInterfaceTask(void *pvParameters) {
    for (;;) {
        // Handle user input
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

// Task creation and initialization
void app_tasks_init(void) {
    xTaskCreate(vSensorTask,        "SensorTask",        SENSOR_TASK_STACK_SIZE,         NULL, SENSOR_TASK_PRIORITY,         &xSensorTaskHandle);
    xTaskCreate(vBubbleLevelTask,   "BubbleLevelTask",   BUBBLE_LEVEL_TASK_STACK_SIZE,   NULL, BUBBLE_LEVEL_TASK_PRIORITY,   &xBubbleLevelTaskHandle);
    xTaskCreate(vRTCTask,           "RTCTask",           RTC_TASK_STACK_SIZE,            NULL, RTC_TASK_PRIORITY,            &xRTCTaskHandle);
    xTaskCreate(vDisplayTask,       "DisplayTask",       DISPLAY_TASK_STACK_SIZE,        NULL, DISPLAY_TASK_PRIORITY,        &xDisplayTaskHandle);
    xTaskCreate(vUserInterfaceTask, "UserInterfaceTask", USER_INTERFACE_TASK_STACK_SIZE, NULL, USER_INTERFACE_TASK_PRIORITY, &xUserInterfaceTaskHandle);
}
