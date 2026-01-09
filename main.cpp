#include "mbed.h"
#include "app/tasks.h"
#include "helper/pin_definition.h"

Serial pc(USBTX,USBRX);

C12832 lcd(p5, p7, p6, p8, p11);
LM75B sensor(p28,p27);
MMA7660 MMA(p28, p27);

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);
DigitalOut led4(LED4);

PwmOut r (p23);
PwmOut g (p24);
PwmOut b (p25);
PwmOut buzzer (p26);

AnalogIn pot1(p19);
AnalogIn pot2(p20);

InterruptIn btnJoystick(p9);  // Joystick center button

AnalogIn pot1(p19);
AnalogIn pot2(p20);

int main() 
{
    pc.baud(115200);
	// Initialize all application tasks
	clock_start();
	app_tasks_init();
	printf("Hello World! Again =)\n");

	// Start the FreeRTOS scheduler
	vTaskStartScheduler();
	// Should never reach here
	while (1) {
		// Optionally, indicate error (e.g., blink LED)
	}
}
