#include "ir.h"

#define BUFFERSIZE 20

typedef struct ir_port {
    uint8_t txBuffer[BUFFERSIZE];
    uint8_t txHead;
    uint8_t txTail;
    uint8_t txBit;
    uint8_t txCount;
    uint8_t txRepeat;

    uint8_t rxCount;
    uint8_t rxBit;
    uint8_t rxByte;
    uint8_t rxLastByte;
    uint8_t rxBuffer[BUFFERSIZE];
    uint8_t rxHead;
    uint8_t rxTail;
    bool rxReset;
} ir_port;

