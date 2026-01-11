#ifndef HITBIT_H
#define HITBIT_H

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"

/**
 * Notification bit used by the joystick ISR -> HitBit task
 */
#define HITBIT_NOTIFY_BTN   (1UL << 0)

/**
 * Attach joystick interrupt handlers and configure ISR-to-task notifications.
 * The driver auto-detects button polarity (active-high/active-low) by sampling the idle level.
 */
void hitbit_attach(TaskHandle_t hitbitTaskHandle);

/**
 * Detach joystick interrupts (useful when HB is disabled).
 */
void hitbit_detach(void);

/**
 * Write a 4-bit pattern to the 4 mbed LEDs.
 * Bit0->LED1, Bit1->LED2, Bit2->LED3, Bit3->LED4
 */
void hitbit_leds_write(uint8_t pattern);

/**
 * Rotate a 4-bit pattern left (circular).
 */
uint8_t hitbit_rotate_left4(uint8_t pattern);

/**
 * Toggle the LED4 bit (bit3).
 * If LED4 was ON -> clear it, else -> add it.
 */
uint8_t hitbit_toggle_led4(uint8_t pattern);

#endif // HITBIT_H
