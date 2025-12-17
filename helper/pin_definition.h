#ifndef PIN_DEFINITION_H
#define PIN_DEFINITION_H

// Pin definitions
#include "mbed.h"
#include "../drivers/LM75B/LM75B.h"
#include "../drivers/C12832/C12832.h"

Serial pc(USBTX,USBRX);

C12832 lcd(p5, p7, p6, p8, p11);
LM75B sensor(p28,p27);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

// i dont know if these leds are the RGB ones



#endif // PIN_DEFINITION_H