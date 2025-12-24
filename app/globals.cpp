
#include "globals.h"

/*State variables in one clean file*/
time_t current_time; // Global variable to hold the current time (updated every second)
struct tm current_time_tm;            //More digestible time, must convert before using though
float gravity_x , gravity_y , gravity_z;
float temperature;
float temperature_max = -273.15; float temperature_min = 15000000.0;
bool Bubble_enable = (bool)BL;
bool HitBit_enable = (bool)HB;
ConfigSound_t ConfigSound = { .enable = (bool)CS , .duty=50 , .period = 0.005 };
bool temp_alarm_flag , time_alarm_flag ;
volatile bool clock_updated = false;