#ifndef HITBIT_H
#define HITBIT_H

#include <stdint.h>

/**
 * Initialize the Hit Bit game
 * Sets up the button interrupt handler
 */
void hitbit_init(void);

/**
 * Display the bit pattern on the 4 LEDs
 * Bit 0 -> LED1, Bit 1 -> LED2, Bit 2 -> LED3, Bit 3 -> LED4
 */
void hitbit_display_leds(uint8_t pattern);

/**
 * Display only the rotating position (cursor)
 * Used during game play to show which LED is the current target
 */
void hitbit_display_rotating(uint8_t pos);

/**
 * Blink all 4 LEDs 3 times to signal WIN
 */
void hitbit_blink_leds_win(void);


//Get the current rotating LED position

uint8_t hitbit_get_rotating_pos(void);

//Set the current rotating LED position
void hitbit_set_rotating_pos(uint8_t pos);

#endif // HITBIT_H

