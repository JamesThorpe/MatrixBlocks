#include "interrupts.h"

void interrupts_init(void) {
    INTCONbits.IPEN = 0;
}


void __interrupt() interrupts_mainIsr(void) {
    if (PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1) {
        isr_millisecondTimer();
        PIR0bits.TMR0IF = 0;
    } else if (PIE5bits.TMR1IE == 1 && PIR5bits.TMR1IF == 1) {
        ir_period();
        PIR5bits.TMR1IF = 0;
        //TODO: reset ir timer interrupt flag
    }
}