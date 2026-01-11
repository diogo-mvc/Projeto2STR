#include "mbed.h"
#include "globals.h"
#include "hitbit.h"
#include "helper/pin_definition.h"

// Keep ISR fast: only notify task
static TaskHandle_t sHitBitTaskHandle = NULL;

static void hitbit_button_isr(void)
{
    if (sHitBitTaskHandle == NULL) return;

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(sHitBitTaskHandle, HITBIT_NOTIFY_BTN, eSetBits, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void hitbit_init(TaskHandle_t hitbitTaskHandle)
{
    sHitBitTaskHandle = hitbitTaskHandle;

    // Choose an initial non-zero pattern so the game makes sense immediately.
    // (If you start at 0x00, you “win” without doing anything.)
    hitbit_current_pattern = 0x0F;   // all bits set initially
    hitbit_rotating = true;

    // Joystick center button is typically active-low on many boards:
 
    btnJoystick.rise(&hitbit_button_isr);
}

void hitbit_deinit(void)
{
    btnJoystick.rise(NULL);
    sHitBitTaskHandle = NULL;
}

void hitbit_display_leds(uint8_t pattern)
{
    pattern &= 0x0F;
    led1 = (pattern >> 0) & 0x01;
    led2 = (pattern >> 1) & 0x01;
    led3 = (pattern >> 2) & 0x01;
    led4 = (pattern >> 3) & 0x01;
}

uint8_t hitbit_rotate_left(uint8_t pattern)
{
    pattern &= 0x0F;
    // circular left rotate on 4 bits
    return (uint8_t)(((pattern << 1) | (pattern >> 3)) & 0x0F);
}

uint8_t hitbit_toggle_led4(uint8_t pattern)
{
    pattern &= 0x0F;
    return (uint8_t)(pattern ^ 0x08); // toggle bit 3
}
