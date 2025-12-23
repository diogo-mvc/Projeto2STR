
#ifndef GLOBALS_H
#define GLOBALS_H

#include <ctime>
#include "../drivers/clock.h" /*to have access to tm struct, otherwise I cannot change inside it*/
#include "../helper/config.h"


/*a strcut tm tem os seguintes campos:*/
/*tm_sec, tm_min , tm_hour*/
/*tm_mday , tm_wday , tm_yday , tm_mon, tm_year*/

struct ConfigSound{ bool enable ; int duty ; float period; };

extern time_t current_time;
extern struct tm current_time_tm;
extern float gravity_x ;
extern float gravity_y ;
extern float gravity_z ;
extern float temperature;
extern bool Bubble_enable , HitBit_enable;
extern ConfigSound soundconfig;
extern bool temp_alarm_flag , time_alarm_flag ;

#endif //GLOBALS_H