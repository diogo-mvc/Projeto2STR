#include "mbed.h"
#include "globals.h"
#include "tasks.h"
#include "helper/pin_definition.h"

// Game state variables
static uint8_t rotating_led_pos = 0;  // Current rotating LED position (0-3)
static uint8_t last_button_press = 0; // Track last button state

// Forward declarations
void hitbit_button_pressed_isr(void);
void hitbit_display_leds(uint8_t pattern);
void hitbit_blink_leds_win(void);

// Interrupt Service Routine for button press

void hitbit_button_pressed_isr(void) {
    // Only process if the rotating position is at LED4 (position 3)
    if (rotating_led_pos == 3) {
        // Check if LED4 (bit 3) already has a bit set
        if (hitbit_current_pattern & 0x08) {
            // LED4 has a bit - clear it
            hitbit_current_pattern &= ~0x08;
        } else {
            // LED4 doesn't have a bit - add one
            hitbit_current_pattern |= 0x08;
        }
        
        // Check for WIN condition - all bits cleared
        if (hitbit_current_pattern == 0x00) {
            // Trigger win sequence
            hitbit_rotating = false;
        }
    }
    
    last_button_press = 1;
}

// Display the bit pattern on the 4 LEDs
void hitbit_display_leds(uint8_t pattern) {
    led1 = (pattern >> 0) & 0x01;
    led2 = (pattern >> 1) & 0x01;
    led3 = (pattern >> 2) & 0x01;
    led4 = (pattern >> 3) & 0x01;
}

// Display only the rotating position (cursor)
// Used during game play to show which LED is the current target
void hitbit_display_rotating(uint8_t pos) {
    uint8_t pattern = (1 << pos) & 0x0F;
    hitbit_display_leds(pattern);
}

// Blink all 4 LEDs 3 times to signal WIN
void hitbit_blink_leds_win(void) {
    int blink_count = 3;
    int i;
    
    for (i = 0; i < blink_count; i++) {
        // Turn on all LEDs
        hitbit_display_leds(0x0F);
        wait(0.2);
        
        // Turn off all LEDs
        hitbit_display_leds(0x00);
        wait(0.2);
    }
}

// Initialize the Hit Bit game
void hitbit_init(void) {
    hitbit_current_pattern = 0x00;
    rotating_led_pos = 0;
    last_button_press = 0;
    hitbit_rotating = true;
    
    // Set up the interrupt on rising edge (button press)
    btnJoystick.rise(&hitbit_button_pressed_isr);
}

// Get the current rotating LED position
uint8_t hitbit_get_rotating_pos(void) {
    return rotating_led_pos;
}

// Set the current rotating LED position
void hitbit_set_rotating_pos(uint8_t pos) {
    rotating_led_pos = pos & 0x03;  // Ensure position stays 0-3
}

