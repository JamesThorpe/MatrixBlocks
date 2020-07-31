#include "matrixblocks.h"


bool millisecondPassed = false;


void main(void) {
    config_init();
    rgb_init();
    status_init();
    interrupts_init();
    interrupts_enableGlobalInterrupts();

    status_pwr_led->on = 1;
    status_sendUpdate();
    
    while(true) {
        if (millisecondPassed) {
            millisecond();
            millisecondPassed = false;
        }
    }
}


void isr_millisecondTimer(void) {
    millisecondPassed = true;
}

void millisecond() {
    rgb_tick();

    //TODO: this should be done in the IR code when not transmitting
    if (rgb_updateDue()) {
        rgb_sendUpdate();
    }
}