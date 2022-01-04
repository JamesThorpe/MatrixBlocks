#ifndef status_h
#define status_h

#include "common.h"

typedef struct status_led {
    bool on;
    uint16_t onCount;
    uint16_t offCount;
    uint16_t counter;
} status_led;

status_led status_leds[7];
status_led* status_pwr_led;


void status_init(void);
void status_sendUpdate(void);
void status_tick(void);
void status_setLed(uint8_t led, bool on);
void status_toggleLed(uint8_t led);
void status_animateLed(uint8_t led, uint16_t onCount, uint16_t offCount);

#endif