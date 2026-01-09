#include "tasks.h"
#include "globals.h"
#include "sensor.h"
#include <cmath>

#define BUZZER_ON  0x01
#define BUZZER_OFF 0x02

SemaphoreHandle_t xPrintMutex;

// Example task handles (if you want to keep references)
TaskHandle_t xSensorTaskHandle        = NULL;
TaskHandle_t xBubbleLevelTaskHandle   = NULL;
TaskHandle_t xDisplayTaskHandle       = NULL;
TaskHandle_t xUserInterfaceTaskHandle = NULL;
TaskHandle_t xAlarmTaskHandle         = NULL;
TaskHandle_t xBuzzerTaskHandle        = NULL;

void vSensorTask(void *pvParameters) {

    uint32_t ulNotificationValue = 0;
    for(;;){
        xTaskNotifyWait(
            0x00,                   // Don’t clear on entry
            0x10, // Clear these on exit
            &ulNotificationValue,
            portMAX_DELAY
        );

        if (ulNotificationValue & 0x10)
        {
            // Read sensor, process data
            temperature = sensor_read_temperature();
            if (temperature > temperature_max){temperature_max = temperature;}
            if (temperature < temperature_min){temperature_min = temperature;}
            if ( (temperature > thigh) || (temperature < tlow) ){ temp_alarm_flag = true; }
            displayRGB(temperature);
        }  

        

        //xSemaphoreTake(xPrintMutex, portMAX_DELAY);
        //printf("Temperature : %f\n",temperature);
        //printf("%s", ctime(&current_time));
        //printf("Gx: %f Gy: %f Gz: %f\n",gravity_x,gravity_y,gravity_z);
        //xSemaphoreGive(xPrintMutex);

        //vTaskDelay(pdMS_TO_TICKS(20));
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
        
        int shift_bubble_x = floor( 16 * gravity_x/(0.984529) );
        int shift_bubble_y = -floor( 16 * gravity_y/(0.984529) );
        display_print_screen(current_time_tm.tm_hour, current_time_tm.tm_min, current_time_tm.tm_sec, \
        true, false, temperature, shift_bubble_x, shift_bubble_y);
        //display_print_screen(12, 34, 56, true, false, 23.5f, 5);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void vUserInterfaceTask(void *pvParameters) {
    for (;;) {
        // Handle user input
        monitor(); /*does not return and is blocked most of the time*/
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

/*mudar isto para o RTC dar o alarme*/
void vAlarmTask(void *pvParameters) {
    time_t alarm_started_time = 0;
    for (;;) {
        if (clock_updated == true){ //spinlock
            current_time_tm = clock_time_to_tm(current_time);
            clock_updated = false;
        }

        if( ((int)current_time % pmon == 0 )||(pmon == 0) ){xTaskNotify(xSensorTaskHandle, 0x10, eSetBits);}

        if (temp_alarm_flag || time_alarm_flag){
            //play buzzer
            xTaskNotify(xBuzzerTaskHandle, BUZZER_ON, eSetBits);
            /*alarm stated now*/
            if (alarm_started_time == 0){alarm_started_time = current_time;}
            
            /*time to shut up*/
            if (current_time - alarm_started_time >= tala){
                //shut up buzzer
                xTaskNotify(xBuzzerTaskHandle, BUZZER_OFF, eSetBits);
                alarm_started_time = 0;
                temp_alarm_flag = false;
                time_alarm_flag = false;
            }
        }

        /*
        uint8_t msg;
        if (xQueueReceive(xBuzzerQueue, &msg, portMAX_DELAY) == pdPASS) {
            // Generate sound using current PWM settings
            //buzzer_play();
        }
        */
        vTaskDelay(pdMS_TO_TICKS(100)); /*trying to give control to the OS but it is still a spinlock ='(*/
    }
}

void vBuzzerTask(void *Parameters){
    uint32_t ulNotificationValue = 0;
    for(;;){
        xTaskNotifyWait(
            0x00,                   // Don’t clear on entry
            BUZZER_ON | BUZZER_OFF, // Clear these on exit
            &ulNotificationValue,
            portMAX_DELAY
        );

        if (ulNotificationValue & BUZZER_ON)
        {
            /*Buzzer_On*/
            //printf("pot1 %u , pot2 %u\n",pot1.read_u16(),pot2.read_u16());
            buzzer = pot1;
            buzzer.period(float(pot2)/220.0);
        }

        if (ulNotificationValue & BUZZER_OFF)
        {
            /*Buzzer_Off*/
            buzzer = 1.0;
        }
    }
}

// Task creation and initialization
void app_tasks_init(void) {

    xPrintMutex = xSemaphoreCreateMutex();
    configASSERT(xPrintMutex != NULL);

    xTaskCreate(vSensorTask,        "SensorTask", SENSOR_TASK_STACK_SIZE, NULL, SENSOR_TASK_PRIORITY, &xSensorTaskHandle);
    xTaskCreate(vBubbleLevelTask,   "BubbleLevelTask", BUBBLE_LEVEL_TASK_STACK_SIZE, NULL, BUBBLE_LEVEL_TASK_PRIORITY, &xBubbleLevelTaskHandle);
    xTaskCreate(vDisplayTask,       "DisplayTask", DISPLAY_TASK_STACK_SIZE, NULL, DISPLAY_TASK_PRIORITY, &xDisplayTaskHandle);
    xTaskCreate(vUserInterfaceTask, "UserInterfaceTask", USER_INTERFACE_TASK_STACK_SIZE, NULL, USER_INTERFACE_TASK_PRIORITY, &xUserInterfaceTaskHandle);
    xTaskCreate(vAlarmTask,         "AlarmTask", ALARM_TASK_STACK_SIZE, NULL, ALARM_TASK_PRIORITY, &xAlarmTaskHandle);
    xTaskCreate(vBuzzerTask,        "BuzzerTask", BUZZER_TASK_STACK_SIZE, NULL, BUZZER_TASK_PRIORITY , &xBuzzerTaskHandle);

}
