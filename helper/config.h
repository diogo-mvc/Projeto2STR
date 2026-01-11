#ifndef INITIAL_CONFIG_H
#define INITIAL_CONFIG_H

#include "pin_definition.h"

#define PMON 5 // monitoring period in seconds [0..99] (0 to disable)
#define TALA 3 // duration of alarm signal in seconds (PWM) [0..60]
#define TLOW 10 // temperature threshold low in degree Celsius [0..50]
#define THIGH 25 // temperature threshold high in degree Celsius [0..50]
#define ALAT 0 // alarm temperature initially disabled (0 - disabled, 1 - enabled)
#define ALAC 0 // alarm clock initially disabled (0 - disabled, 1 - enabled)
#define ALAH 12 // alarm clock hours [0..23]
#define ALAM 0 // alarm clock minutes [0..59]
#define ALAS 0 // alarm clock seconds [0..59]
#define BL 1 // Bubble Level active (0 - inactive, 1 - active)
#define HB 0 // Hit Bit inactive (0 - inactive, 1 - active)
#define CS 0 // Config Sound inactive (0 - inactive, 1 - active)

#endif // INITIAL_CONFIG_H
