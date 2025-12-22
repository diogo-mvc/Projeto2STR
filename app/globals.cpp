
#include "globals.h"

/*State variables in one clean file*/
volatile time_t current_time; // Global variable to hold the current time (updated every second)
struct tm current_time_tm;            //More digestible time, must convert before using though
float gravity_x , gravity_y , gravity_z;
float temperature;
bool Bubble_enable , HitBit_enable;
ConfigSound soundconfig = { false , 50 , 0.005 };
bool temp_alarm_flag , time_alarm_flag ;