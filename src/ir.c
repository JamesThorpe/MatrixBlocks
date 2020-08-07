#include "ir.h"

#define BUFFERSIZE 20

/*
  TX is on Port A
  0 = IR 1
  1 = IR 2
  2 = IR 3
  3 = IR 4
  4 = IR 5
  5 = IR 6

  RX is on Port F
  7 = IR 1
  6 = IR 2
  5 = IR 3
  4 = IR 4
  3 = IR 5
  2 = IR 6

*/

#define IROFF 3
#define IRZERO 3
#define IRONE 6
#define IRRESET 9

typedef struct ir_port {
    uint8_t txBuffer[BUFFERSIZE];
    uint8_t txHead;
    uint8_t txTail;
    uint8_t txBit;
    uint8_t txCount;
    uint8_t txRepeat;
    uint8_t txMaskHigh;
    uint8_t txMaskLow;

    uint8_t rxCount;
    uint8_t rxBit;
    uint8_t rxByte;
    uint8_t rxLastByte;
    uint8_t rxBuffer[BUFFERSIZE];
    uint8_t rxHead;
    uint8_t rxTail;
    bool rxReset;
} ir_port;

ir_port ir_ports[6];
ir_port *ir_port1 = &ir_ports[0];
ir_port *ir_port2 = &ir_ports[1];
ir_port *ir_port3 = &ir_ports[2];
ir_port *ir_port4 = &ir_ports[3];
ir_port *ir_port5 = &ir_ports[4];
ir_port *ir_port6 = &ir_ports[5];

void ir_init(void) {
    for (uint8_t x = 0; x < 6; x++) {
        ir_ports[x].txHead = 0;
        ir_ports[x].txTail = 0;
        ir_ports[x].txBit = 0;
        ir_ports[x].txCount = 0;
        ir_ports[x].txMaskHigh = 1 << x;
        ir_ports[x].txMaskLow = ~ir_ports[x].txMaskHigh;

        ir_ports[x].rxCount = 0;
        ir_ports[x].rxHead = 0;
        ir_ports[x].rxTail = 0;
        ir_ports[x].rxLastByte = 0;
    }
}
