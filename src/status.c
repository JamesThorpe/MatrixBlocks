#include "status.h"

//Status LEDs are on Port E (along with the buzzer)


void status_init(void) {
    status_pwr_led = &status_leds[0];
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
    LATE = (LATE & 0xFD) | out; //Buzzer is on bit 2, don't change that pin
}