#ifndef APP_DISPLAY_H
#define APP_DISPLAY_H



// Include necessary headers
#include "../drivers/C12832/C12832.h"
#include "../helper/pin_definition.h"

#ifdef __cplusplus
extern "C" {
#endif


void display_clear(void);
void display_draw_hline(int y, int x_start, int x_end);
void display_draw_vline(int x, int y_start, int y_end);

void display_print_time(int hour, int min, int sec);
void display_print_alarm_status(bool alarm_clock_enabled, bool temp_alarm_enabled);
void display_print_temperature(float temperature);
void display_print_bubble_level(int value);

void display_init(void);
void display_print_screen(int hour, int min, int sec, bool alarm_clock_enabled, bool temp_alarm_enabled, float temp, int bubble_level);

#ifdef __cplusplus
}
#endif

#endif // APP_DISPLAY_H