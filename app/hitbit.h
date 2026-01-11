#ifndef HITBIT_H
#define HITBIT_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/**
 * Notification bit used by the HitBit ISR -> task
 */
#define HITBIT_NOTIFY_BTN   (1UL << 0)

/**
 * Initialize the Hit Bit game and attach the joystick interrupt.
 * Pass the HitBit task handle so the ISR can notify it.
 */
void hitbit_init(TaskHandle_t hitbitTaskHandle);

/**
 * Detach interrupt (optional but useful if you want).
 */
void hitbit_deinit(void);

/**
 * Display the bit pattern on the 4 LEDs
 * Bit 0 -> LED1, Bit 1 -> LED2, Bit 2 -> LED3, Bit 3 -> LED4
 */
void hitbit_display_leds(uint8_t pattern);

/**
 * Rotate the current 4-bit pattern by 1 position (circular).
 * Direction doesn’t matter for the spec; pick one and be consistent.
 */
uint8_t hitbit_rotate_left(uint8_t pattern);

/**
 * Toggle the LED4 bit (bit 3): if 1 -> 0, if 0 -> 1
 */
uint8_t hitbit_toggle_led4(uint8_t pattern);

#endif // HITBIT_H
