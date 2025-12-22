
#include "../app/globals.h"
#include "clock.h"


//volatile time_t current_time = 0;

typedef void (*clock_user_callback_t)(void);
static clock_user_callback_t user_callback = NULL;

static void clock_callback(void) {
    current_time = time(NULL);
    current_time_tm = clock_time_to_tm(current_time); /*maybe this line should not be inside a callback?*/
    if (user_callback) {
        user_callback();
    }
}

// User can set their own callback (optional)
void clock_user_callback(clock_user_callback_t cb) {
    user_callback = cb;
}

void clock_start(void) {
    RTC::attach(&clock_callback, RTC::Second);
}

// Convert time_t to struct tm (local time)
struct tm clock_time_to_tm(time_t t) {
    struct tm result;
    struct tm *tmp = localtime(&t);
    if (tmp) {
        result = *tmp;
    } else {
        // If conversion fails, zero out the struct
        result = NULL;
    }
    return result;
}

// Convert struct tm to time_t
time_t clock_tm_to_time(const struct tm* t) {
    if (t) {
        return mktime((struct tm*)t);
    } else {
        return (time_t)-1;
    }
}

