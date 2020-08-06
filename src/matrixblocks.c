#include "matrixblocks.h"


bool millisecondPassed = false;


void main(void) {
    config_init();
    rgb_init();
    status_init();
    interrupts_init();
    interrupts_enableGlobalInterrupts();

    status_setLed(0, true);
    
    while(true) {
        if (millisecondPassed) {
            millisecond();
            millisecondPassed = false;
        }

        for (uint8_t x = 0; x < 6; x++) {
            if (button_isPressed(&buttons[x])) {
                if (status_leds[x + 1].counter == 0) {
                    status_animateLed(x + 1, 200, 800);
                } else {
                    status_setLed(x + 1, false);
                }
            }
        }
    }
}


void isr_millisecondTimer(void) {
    millisecondPassed = true;
}

void millisecond() {
    rgb_tick();
    status_tick();
    button_tick();

    //TODO: this should be done in the IR code when not transmitting
    if (rgb_updateDue()) {
        rgb_sendUpdate();
    }
}