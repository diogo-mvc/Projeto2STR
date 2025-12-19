#include "mbed.h"
#include "app/tasks.h"

int main() 
{
    pc.baud(115200);
	// Initialize all application tasks
	clock_start();
	app_tasks_init();

	// Start the FreeRTOS scheduler
	vTaskStartScheduler();
	// Should never reach here
	while (1) {
		// Optionally, indicate error (e.g., blink LED)
	}
}
