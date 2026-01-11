#include "mbed.h"
#include "hitbit.h"
#include "helper/pin_definition.h"

// Keep ISR fast: only notify the HitBit task
static TaskHandle_t sHitBitTaskHandle = NULL;

// Auto-detected "pressed" logic level (0 or 1)
static int  sPressedLevel = 1;
static bool sPressedLevelValid = false;

// NOTE: Using InterruptIn callbacks caused a mbed fault on this target.
// To be robust we use a polling-based approach inside the HitBit task so
// the button is handled entirely in task context (no ISRs). 

void hitbit_attach(TaskHandle_t hitbitTaskHandle)
{
    sHitBitTaskHandle = hitbitTaskHandle;

    // Detect idle level once; pressed is assumed to be the opposite.
    // This makes it work for both active-high and active-low wiring.
    const int idle = btnJoystick.read();
    sPressedLevel = (idle == 0) ? 1 : 0;
    sPressedLevelValid = true;

    // No hardware interrupts when using the polling approach. The HitBit
    // task will monitor the pin in task context and handle presses; this
    // avoids any ISR-related platform faults.
}

void hitbit_detach(void)
{
    // No InterruptIn handlers are attached when using the polling approach.
    // Just clear state so the HitBit task will stop monitoring.
    sHitBitTaskHandle = NULL;
    sPressedLevelValid = false;
}

void hitbit_leds_write(uint8_t pattern)
{
    pattern &= 0x0F;
    led1 = (pattern >> 0) & 0x01;
    led2 = (pattern >> 1) & 0x01;
    led3 = (pattern >> 2) & 0x01;
    led4 = (pattern >> 3) & 0x01;
}

uint8_t hitbit_rotate_left4(uint8_t pattern)
{
    pattern &= 0x0F;
    // circular left rotate on 4 bits
    return (uint8_t)(((pattern << 1) | (pattern >> 3)) & 0x0F);
}

uint8_t hitbit_toggle_led4(uint8_t pattern)
{
    pattern &= 0x0F;
    return (uint8_t)(pattern ^ 0x08); // toggle bit3 (LED4)
}