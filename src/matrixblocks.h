#ifndef matrixblocks_h
#define matrixblocks_h

#ifdef _vscode
#include "helpers/vscode.h"
#else
#include <xc8.h>
#endif

#include "interrupts.h"
#include "rgb.h"
#include "status.h"

void main(void);
void isr_millisecondTimer(void);
void millisecond(void);


#endif