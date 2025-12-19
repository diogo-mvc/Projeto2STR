#include "tasks.h"

// Example task handles (if you want to keep references)
TaskHandle_t xSensorTaskHandle = NULL;
TaskHandle_t xBubbleLevelTaskHandle = NULL;
TaskHandle_t xRTCTaskHandle = NULL;
TaskHandle_t xDisplayTaskHandle = NULL;
TaskHandle_t xUserInterfaceTaskHandle = NULL;

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

void vAlarmTask(void *pvParameters) {
    for (;;) {
        uint8_t msg;
        if (xQueueReceive(xBuzzerQueue, &msg, portMAX_DELAY) == pdPASS) {
            // Generate sound using current PWM settings
            buzzer_play();
        }
    }
}

// Task creation and initialization
void app_tasks_init(void) {
    xTaskCreate(vSensorTask, "SensorTask", SENSOR_TASK_STACK_SIZE, NULL, SENSOR_TASK_PRIORITY, &xSensorTaskHandle);
    xTaskCreate(vBubbleLevelTask, "BubbleLevelTask", BUBBLE_LEVEL_TASK_STACK_SIZE, NULL, BUBBLE_LEVEL_TASK_PRIORITY, &xBubbleLevelTaskHandle);
    xTaskCreate(vDisplayTask, "DisplayTask", DISPLAY_TASK_STACK_SIZE, NULL, DISPLAY_TASK_PRIORITY, &xDisplayTaskHandle);
    xTaskCreate(vUserInterfaceTask, "UserInterfaceTask", USER_INTERFACE_TASK_STACK_SIZE, NULL, USER_INTERFACE_TASK_PRIORITY, &xUserInterfaceTaskHandle);
    xTaskCreate(vAlarmTask, "AlarmTask", ALARM_TASK_STACK_SIZE, NULL, ALARM_TASK_PRIORITY, &xAlarmTaskHandle);
}
