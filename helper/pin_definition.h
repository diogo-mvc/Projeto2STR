#ifndef PIN_DEFINITION_H
#define PIN_DEFINITION_H

// Pin definitions
#include "mbed.h"
#include "../drivers/LM75B/LM75B.h"
#include "../drivers/C12832/C12832.h"

extern Serial pc;

extern C12832 lcd;
extern LM75B sensor;
extern DigitalOut led1;
extern DigitalOut led2;
extern DigitalOut led3;
extern DigitalOut led4;

// i dont know if these leds are the RGB ones



#endif // PIN_DEFINITION_H