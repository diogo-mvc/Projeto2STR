
#include "../app/globals.h"
#include "clock.h"


//volatile time_t current_time = 0;

typedef void (*clock_user_callback_t)(void);
static clock_user_callback_t user_callback = NULL;

static void clock_callback(void) {
    //current_time = time(NULL);
    current_time += 1;
    clock_updated = true;
    //printf("%s", ctime(&current_time)); /*printf bloqueia o I2C->mau debug*/
    /*
    if (user_callback) {
        user_callback();
    }*/
}

// User can set their own callback (optional)
void clock_user_callback(clock_user_callback_t cb) {
    user_callback = cb;
}

void clock_start(void) {
    set_time(1766361600);
    current_time_tm = RTC::getDefaultTM();
    RTC::attach(&clock_callback, RTC::Second);
    current_time = 1766361600;
}

// Convert time_t to struct tm (local time)
struct tm clock_time_to_tm(time_t t) {
    struct tm result;
    struct tm *tmp = localtime(&t);
    if (tmp) {
        result = *tmp;
    } else {
        // If conversion fails, zero out the struct
        //result = NULL;
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

