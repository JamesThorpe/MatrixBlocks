#include "matrixblocks.h"


bool millisecondPassed = false;


void main(void) {
    config_init();
    rgb_init();
    status_init();
    interrupts_init();
    interrupts_enableGlobalInterrupts();

    
    status_setLed(0, true);
    
    status_animateLed(1, 200, 800);
    status_animateLed(2, 300, 700);
    status_animateLed(3, 400, 600);
    status_animateLed(4, 500, 500);
    status_animateLed(5, 600, 400);
    status_animateLed(6, 700, 300);
    
    while(true) {
        if (millisecondPassed) {
            millisecond();
            millisecondPassed = false;
        }

        /*for (uint8_t x = 0; x < 6; x++) {
            if (button_isPressed(&buttons[x])) {
                if (status_leds[x + 1].counter == 0) {
                    status_animateLed(x + 1, 200, 800);
                } else {
                    status_setLed(x + 1, false);
                }
            }
        }*/
    }
}


void isr_millisecondTimer(void) {
    millisecondPassed = true;
}

void millisecond() {
    //rgb_tick();
    status_tick();
    //button_tick();

    //TODO: this should be done in the IR code when not transmitting
    //if (rgb_updateDue()) {
    //    rgb_sendUpdate();
    //}
}