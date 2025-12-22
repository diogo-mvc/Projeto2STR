
#include "alarm.h"

// Set or change an alarm
void clock_set_alarm(const struct tm* alarm_time, void (*clock_alarm_callback)(void)) {
    if (alarm_time && clock_alarm_callback) {
        RTC::alarm(clock_alarm_callback, *alarm_time);
    }
}

// Disable the alarm
void clock_disable_alarm(void) {
    RTC::alarmOff();
}

// Alarm callback
void clock_alarm_callback(void) {
    // Sound the buzzer for tala with a pwm signal
    // supposed to be handled by a specific task??
    uint8_t msg = 1;
    //xQueueSendFromISR(xAlarmQueue, &msg, NULL);
    printf("[ALARM] Alarm triggered!\n");
}

