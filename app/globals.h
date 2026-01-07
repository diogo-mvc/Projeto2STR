
#ifndef GLOBALS_H
#define GLOBALS_H

#include <ctime>
#include "../drivers/clock.h" /*to have access to tm struct, otherwise I cannot change inside it*/
#include "../helper/config.h"


/*a strcut tm tem os seguintes campos:*/
/*tm_sec, tm_min , tm_hour*/
/*tm_mday , tm_wday , tm_yday , tm_mon, tm_year*/

typedef struct { bool enable ; int duty ; float period; } ConfigSound_t;
extern ConfigSound_t ConfigSound;

extern time_t current_time;
extern struct tm current_time_tm;
extern float gravity_x ;
extern float gravity_y ;
extern float gravity_z ;
extern float temperature;
extern float temperature_max; extern float temperature_min;
extern bool Bubble_enable , HitBit_enable;
extern bool temp_alarm_flag , time_alarm_flag ;
extern volatile bool clock_updated ;

extern int pmon ;
extern int tala ;
extern float tlow; 
extern float thigh;

#endif //GLOBALS_H
