#include "interrupts.h"

void interrupts_init(void) {
    INTCONbits.IPEN = 0;
}


void __interrupt() interrupts_mainIsr(void) {
    if (PIE5bits.TMR2IE == 1 && PIR5bits.TMR2IF == 1) {
        ir_period();
        PIR5bits.TMR2IF = 0;
    } else if (PIE0bits.TMR0IE == 1 && PIR0bits.TMR0IF == 1) {
        isr_millisecondTimer();
        PIR0bits.TMR0IF = 0;
    } 
}