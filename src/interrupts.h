#ifndef interrupts_h
#define interrupts_h

#include "matrixblocks.h"

#define interrupts_enableGlobalInterrupts() (INTCON0bits.GIE = 1)
#define interrupts_disableGlobalInterrupts() (INTCON0bits.GIE = 0)

void interrupts_init(void);

#endif