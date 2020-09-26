#ifndef matrixblocks_h
#define matrixblocks_h

#include "common.h"

#include "config.h"
#include "interrupts.h"
#include "rgb.h"
#include "status.h"
#include "button.h"
#include "ir.h"
#include "communications.h"

void main(void);
void isr_millisecondTimer(void);
void isr_microsecondTimer(void);
void millisecond(void);

void HandleMessage(uint8_t side, uint8_t msgType, uint8_t msgbytes[], uint8_t msglength);

#endif