#ifndef CLOCK_H
#define CLOCK_H



#include "RTC/RTC.h"
#include <ctime>
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

void alarmFunction( void );

// Initialize the RTC interrupt to call the callback every second
void clock_start(void);

// Optional: set a user callback to be called every second
typedef void (*clock_user_callback_t)(void);
void clock_user_callback(clock_user_callback_t cb);


// Convert time_t to struct tm (local time)
struct tm clock_time_to_tm(time_t t);

// Convert struct tm to time_t
time_t clock_tm_to_time(const struct tm* t);

#ifdef __cplusplus
}
#endif

#endif // CLOCK_H
