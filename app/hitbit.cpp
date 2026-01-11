#include "mbed.h"
#include "hitbit.h"
#include "helper/pin_definition.h"

// Keep ISR fast: only notify the HitBit task
static TaskHandle_t sHitBitTaskHandle = NULL;

// Auto-detected "pressed" logic level (0 or 1)
static int  sPressedLevel = 1;
static bool sPressedLevelValid = false;

static void hitbit_button_isr(void)
{
    if (sHitBitTaskHandle == NULL || !sPressedLevelValid) {
        return;
    }

    // InterruptIn is also a DigitalIn, so read() is valid
    const int level = btnJoystick.read();

    // Only treat the interrupt as a "press" if pin is at the pressed level.
    // (This avoids triggering on release when both edges are attached.)
    if (level != sPressedLevel) {
        return;
    }

    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xTaskNotifyFromISR(
        sHitBitTaskHandle,
        HITBIT_NOTIFY_BTN,
        eSetBits,
        &xHigherPriorityTaskWoken
    );
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void hitbit_attach(TaskHandle_t hitbitTaskHandle)
{
    sHitBitTaskHandle = hitbitTaskHandle;

    // Detect idle level once; pressed is assumed to be the opposite.
    // This makes it work for both active-high and active-low wiring.
    const int idle = btnJoystick.read();
    sPressedLevel = (idle == 0) ? 1 : 0;
    sPressedLevelValid = true;

    // Attach both edges; ISR filters by pressed level
    btnJoystick.rise(&hitbit_button_isr);
    btnJoystick.fall(&hitbit_button_isr);
}

void hitbit_detach(void)
{
    btnJoystick.rise(NULL);
    btnJoystick.fall(NULL);
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
