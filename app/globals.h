
#ifndef GLOBALS_H
#define GLOBALS_H

#include <ctime>
#include "../drivers/clock.h" /*to have access to tm struct, otherwise I cannot change inside it*/

struct ConfigSound{ bool enable ; int duty ; float period; };

extern volatile time_t current_time;
extern struct tm current_time_tm;
extern float gravity_x , gravity_y , gravity_z;
extern float temperature;
extern bool Bubble_enable , HitBit_enable;
extern ConfigSound soundconfig;
extern bool temp_alarm_flag , time_alarm_flag ;

#endif //GLOBALS_H