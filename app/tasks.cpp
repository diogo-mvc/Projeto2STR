#include "tasks.h"
#include "globals.h"
#include "sensor.h"


SemaphoreHandle_t xPrintMutex;

// Example task handles (if you want to keep references)
TaskHandle_t xSensorTaskHandle        = NULL;
TaskHandle_t xBubbleLevelTaskHandle   = NULL;
TaskHandle_t xDisplayTaskHandle       = NULL;
TaskHandle_t xUserInterfaceTaskHandle = NULL;
TaskHandle_t xAlarmTaskHandle        = NULL;

void vSensorTask(void *pvParameters) {
    for (;;) {
        // Read sensor, process data
        temperature = sensor_read_temperature();
        if (temperature > temperature_max){temperature_max = temperature;}
        if (temperature < temperature_min){temperature_min = temperature;}

        //xSemaphoreTake(xPrintMutex, portMAX_DELAY);
        //printf("Temperature : %f\n",temperature);
        //printf("%s", ctime(&current_time));
        //printf("Gx: %f Gy: %f Gz: %f\n",gravity_x,gravity_y,gravity_z);
        //xSemaphoreGive(xPrintMutex);

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void vBubbleLevelTask(void *pvParameters) {
    for (;;) {
        // Update bubble level display
        sensor_read_gravity();
        vTaskDelay(pdMS_TO_TICKS(150));
    }
}

void vDisplayTask(void *pvParameters) {

    display_init();
    for (;;) {
        
        display_print_screen(current_time_tm.tm_hour, current_time_tm.tm_min, current_time_tm.tm_sec, true, false, temperature, 5);
        //display_print_screen(12, 34, 56, true, false, 23.5f, 5);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void vUserInterfaceTask(void *pvParameters) {
    for (;;) {
        // Handle user input
        monitor(); /*does not return and is blocked must of the time*/
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vAlarmTask(void *pvParameters) {
    for (;;) {
        if (clock_updated == true){current_time_tm = clock_time_to_tm(current_time); clock_updated = false;}
        /*
        uint8_t msg;
        if (xQueueReceive(xBuzzerQueue, &msg, portMAX_DELAY) == pdPASS) {
            // Generate sound using current PWM settings
            //buzzer_play();
        }
        */
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

// Task creation and initialization
void app_tasks_init(void) {

    xPrintMutex = xSemaphoreCreateMutex();
    configASSERT(xPrintMutex != NULL);

    xTaskCreate(vSensorTask, "SensorTask", SENSOR_TASK_STACK_SIZE, NULL, SENSOR_TASK_PRIORITY, &xSensorTaskHandle);
    xTaskCreate(vBubbleLevelTask, "BubbleLevelTask", BUBBLE_LEVEL_TASK_STACK_SIZE, NULL, BUBBLE_LEVEL_TASK_PRIORITY, &xBubbleLevelTaskHandle);
    xTaskCreate(vDisplayTask, "DisplayTask", DISPLAY_TASK_STACK_SIZE, NULL, DISPLAY_TASK_PRIORITY, &xDisplayTaskHandle);
    xTaskCreate(vUserInterfaceTask, "UserInterfaceTask", USER_INTERFACE_TASK_STACK_SIZE, NULL, USER_INTERFACE_TASK_PRIORITY, &xUserInterfaceTaskHandle);
    xTaskCreate(vAlarmTask, "AlarmTask", ALARM_TASK_STACK_SIZE, NULL, ALARM_TASK_PRIORITY, &xAlarmTaskHandle);
}
