#include "interrupts.h"

void interrupts_init(void) {
    INTCONbits.IPEN = 0;
}


void __interrupt() interrupts_mainIsr(void) {
    if (PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1) {
        isr_millisecondTimer();
        PIR0bits.TMR0IF = 0;
    } else if (false) { //TODO: Check ir timer interrupt flag

        //TODO: reset ir timer interrupt flag
    }
}