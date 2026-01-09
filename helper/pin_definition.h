#ifndef PIN_DEFINITION_H
#define PIN_DEFINITION_H

// Pin definitions
#include "mbed.h"
#include "../drivers/LM75B/LM75B.h"
#include "../drivers/C12832/C12832.h"
#include "../drivers/MMA7600/MMA7660.h"

extern Serial pc;

extern C12832 lcd;
extern LM75B sensor;
extern MMA7660 MMA;
extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;
extern DigitalOut led4;

extern PwmOut r ;
extern PwmOut g ;
extern PwmOut b ;
extern PwmOut buzzer;

extern AnalogIn pot1;
extern AnalogIn pot2;

extern InterruptIn btnJoystick;  // Joystick center button

#endif // PIN_DEFINITION_H
