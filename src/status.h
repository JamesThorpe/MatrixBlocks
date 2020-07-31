#ifndef status_h
#define status_h

#include "matrixblocks.h"

typedef struct status_led {
    bool on;
} status_led;

status_led status_leds[7];
status_led* status_pwr_led;


void status_init(void);
void status_sendUpdate(void);



#endif