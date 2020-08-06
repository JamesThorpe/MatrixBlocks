#include "status.h"

//Status LEDs are on Port E (along with the buzzer)


void status_init(void) {
    
}


void status_sendUpdate(void) {
    uint8_t out = 0;
    if (status_pwr_led->on) {
        out = 1;
    }
    for (uint8_t x = 1; x < 7; x++) {
        if (status_leds[x].on) {
            out |= 1 << (8-x);
        }
    }

    // Buzzer is on bit 1 of the port, so mask with 0xFD so we
    // don't change that pin
    LATE = (LATE & 0xFD) | out; 
}

void status_animateLed(uint8_t led, uint16_t onCount, uint16_t offCount) {
    status_leds[led].on = true;
    status_leds[led].onCount = status_leds[led].counter = onCount;
    status_leds[led].offCount = offCount;
}

bool externalUpdate = false;
void status_setLed(uint8_t led, bool on) {
    status_leds[led].on = on;
    status_leds[led].counter = 0;
    externalUpdate = true;
}

void status_tick(void) {
    bool isUpdateNeeded = false;

    for (uint8_t x = 0; x < 7; x++) {
        status_led* led = &status_leds[x];
        if (led->counter > 0) {
            led->counter--;
            if (led->counter == 0) {
                if (led->on) {
                    led->counter = led->offCount;
                    led->on = false;
                    isUpdateNeeded = true;
                } else {
                    led->counter = led->onCount;
                    led->on = true;
                    isUpdateNeeded = true;
                }
            }
        }
    }

    if (isUpdateNeeded || externalUpdate) {
        externalUpdate = false;
        status_sendUpdate();
    }
}