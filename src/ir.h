#ifndef ir_h
#define ir_h

#include "common.h"

#define BUFFERSIZE 20
typedef struct ir_port {
    volatile uint8_t txBuffer[BUFFERSIZE];
    volatile uint8_t txHead;
    volatile uint8_t txTail;
    volatile uint8_t txMaskHigh;
    volatile uint8_t txMaskLow;
    volatile uint8_t txActive;

    volatile uint8_t rxCount;
    volatile uint8_t rxBit;
    volatile uint8_t rxByte;
    volatile uint8_t rxLastByte;
    volatile uint8_t rxBuffer[BUFFERSIZE];
    volatile uint8_t rxHead;
    volatile uint8_t rxTail;
    volatile uint8_t rxMaskHigh;
    bool rxReset;
} ir_port;

ir_port ir_ports[6];
ir_port *ir_port1 = &ir_ports[0];
ir_port *ir_port2 = &ir_ports[1];
ir_port *ir_port3 = &ir_ports[2];
ir_port *ir_port4 = &ir_ports[3];
ir_port *ir_port5 = &ir_ports[4];
ir_port *ir_port6 = &ir_ports[5];

void ir_init(void);
void ir_period(void);
void ir_send(ir_port* port, uint8_t data);
int8_t ir_isReady(ir_port* port);
uint8_t ir_read(ir_port* port);

#endif