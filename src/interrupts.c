#include "interrupts.h"

void interrupts_init(void) {
    INTCON0bits.IPEN = 0;
}


void __interrupt() interrupts_mainIsr(void) {
    if (false) { //TODO: Check ms timer interrupt flag
        isr_millisecondTimer();
        //TODO: reset ms timer interrupt flag
    } else if (false) { //TODO: Check ir timer interrupt flag

        //TODO: reset ir timer interrupt flag
    } else if (false) { //TODO: check button interrupt flag

        //TODO: reset button interrupt flag
    }
}