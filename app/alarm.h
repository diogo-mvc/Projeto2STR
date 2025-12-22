#ifndef ALARM_H
#define ALARM_H



#include "../drivers/clock.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// Set or change an alarm (calls cb at the specified time)
void clock_set_alarm(const struct tm* alarm_time, void (*cb)(void));

// Disable the alarm
void clock_disable_alarm(void);

// Example alarm callback
void clock_alarm_callback(void);

#ifdef __cplusplus
}
#endif

#endif // ALARM_H
