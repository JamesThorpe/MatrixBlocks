#ifndef interrupts_h
#define interrupts_h

#include "matrixblocks.h"

#define interrupts_enableGlobalInterrupts() (INTCONbits.GIE = 1)
#define interrupts_disableGlobalInterrupts() (INTCONbits.GIE = 0)

void interrupts_init(void);

#endif