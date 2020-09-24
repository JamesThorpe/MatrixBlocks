#ifndef ir_h
#define ir_h

#include "common.h"

#define BUFFERSIZE 20
typedef struct ir_port {
    uint8_t txBuffer[BUFFERSIZE];
    uint8_t txHead;
    uint8_t txTail;
    uint8_t txMaskHigh;
    uint8_t txMaskLow;
    uint8_t txActive;

    uint8_t rxCount;
    uint8_t rxBit;
    uint8_t rxByte;
    uint8_t rxLastByte;
    uint8_t rxBuffer[BUFFERSIZE];
    uint8_t rxHead;
    uint8_t rxTail;
    uint8_t rxMaskHigh;
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
uint8_t ir_isReady(ir_port* port);
uint8_t ir_read(ir_port* port);

#endif