#include "ir.h"
#include "rgb.h"

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

#define IRZERO 3
#define IRONE 6
#define IRZEROOFF 6
#define IRONEOFF 3

#define IRRESET 9
#define IRRESETOFF 3
#define IRBIT IRONE + IRZERO

uint8_t txState;
#define TXIDLE 0
#define TXRESET 1
#define TXBYTE 2

uint8_t txCount;
uint8_t txBit;
uint8_t txRepeat;

void ir_init(void) {
    txState = TXIDLE;
    txCount = 0;
    for (uint8_t x = 0; x < 6; x++) {
        ir_ports[x].txHead = 0;
        ir_ports[x].txTail = 0;
        ir_ports[x].txMaskHigh = 1 << x;
        ir_ports[x].txMaskLow = ~ir_ports[x].txMaskHigh;
        ir_ports[x].txActive = 0;

        ir_ports[x].rxCount = 0;
        ir_ports[x].rxHead = 0;
        ir_ports[x].rxTail = 0;
        ir_ports[x].rxLastByte = 0;
        ir_ports[x].rxMaskHigh = (1 << (8-x));
    }

}

void ir_tx(void) {
    if (txState == TXRESET) {
        if (txCount == 0) {
            //Start of reset, turn on LEDs on ports sending data
            uint8_t txByte = 0;
            for (uint8_t x = 0; x < 6; x++) {
                if (ir_ports[x].txActive) {
                    txByte |= ir_ports[x].txMaskHigh;
                }
            }
            LATA = (LATA & 0xC0) | txByte;
            txCount = IRRESET + IRRESETOFF;
            txRepeat = 2;
        } else {
            txCount--;
            if (txCount == IRRESETOFF) {
                //Part way through reset, turn off all LEDs
                LATA = (LATA & 0xC0);
            } else if (txCount == 0) {
                //End of reset, transition into first bit of byte on ports sending data
                txState = TXBYTE;
                uint8_t txByte = 0;
                for (uint8_t x = 0; x < 6; x++) {
                    if (ir_ports[x].txActive) {
                        txByte |= ir_ports[x].txMaskHigh;
                    }
                }
                LATA = (LATA & 0xC0) | txByte;
                txCount = IRBIT;
            }
        }
    } else if (txState == TXBYTE) {
        if (txCount || txBit) {
            if (txCount) {
                //mid bit, check counters and turn off LEDs when necessary
                txCount--;
                uint8_t txByte = 0;
                if (txCount == IRZEROOFF) {
                    uint8_t txByte = LATA;
                    for (uint8_t x = 0; x < 6; x++) {
                        if (ir_ports[x].txActive && !(ir_ports[x].txBuffer[ir_ports[x].txTail] & (1<<(7-txBit)))) {
                            txByte &= ir_ports[x].txMaskLow;
                        }
                    }
                    LATA = txByte;
                } else if (txCount == IRONEOFF) {
                    uint8_t txByte = LATA;
                    for (uint8_t x = 0; x < 6; x++) {
                        if (ir_ports[x].txActive && (ir_ports[x].txBuffer[ir_ports[x].txTail] & (1<<(7-txBit)))) {
                            txByte &= ir_ports[x].txMaskLow;
                        }
                    }
                    LATA = txByte;
                }
            } else {
                //new bit, reset counter and turn LEDs back on
                txBit--;
                txCount = IRBIT;
                uint8_t txByte = 0;
                for (uint8_t x = 0; x < 6; x++) {
                    if (ir_ports[x].txActive) {
                        txByte |= ir_ports[x].txMaskHigh;
                    }
                }
                LATA = (LATA & 0xC0) | txByte;                
            }
        } else if (txRepeat) {
            //repeat the byte
            txRepeat--;
            txBit = 8;
            txCount = IRBIT;
            uint8_t txByte = 0;
            for (uint8_t x = 0; x < 6; x++) {
                if (ir_ports[x].txActive) {
                    txByte |= ir_ports[x].txMaskHigh;
                }
            }
            LATA = (LATA & 0xC0) | txByte;
        } else {
            txState = TXIDLE;
        }
    } else if (txState == TXIDLE) {
        if (rgb_updateDue()) {
            rgb_sendUpdate();
            for (uint8_t x = 0; x < 6; x++) {
                ir_ports[x].rxReset = true;
            }
        }

        for (uint8_t x = 0; x < 6; x++) {
            if (ir_ports[x].txHead != ir_ports[x].txTail) {
                if (++(ir_ports[x].txTail) == BUFFERSIZE) {
                    ir_ports[x].txTail = 0;
                }
                ir_ports[x].txActive = true;
                txState = TXRESET;
            } else {
                ir_ports[x].txActive = false;
            }
        }
    }
}

void ir_rx(void) {
    uint8_t rx = PORTF;
    for (uint8_t x = 0; x < 6; x++) {
        if (rx & ir_ports[x].rxMaskHigh) {
            if (ir_ports[x].rxCount >= IRRESET - 1) {
                ir_ports[x].rxBit = 0;
                ir_ports[x].rxByte = 0;
                ir_ports[x].rxReset = false;
            } else if (ir_ports[x].rxCount >= IRONE - 1) {
                ir_ports[x].rxByte |= (1<<ir_ports[x].rxBit);
                ir_ports[x].rxBit++;
            } else if (ir_ports[x].rxCount) {
                ir_ports[x].rxBit++;
            }
            ir_ports[x].rxCount = 0;

            if (ir_ports[x].rxBit == 8 && !ir_ports[x].rxReset) {
                ir_ports[x].rxBit = 0;
                if (ir_ports[x].rxByte != ir_ports[x].rxLastByte) {
                    ir_ports[x].rxLastByte = ir_ports[x].rxByte;
                    ir_ports[x].rxBuffer[ir_ports[x].rxHead] = ir_ports[x].rxByte;
                    if (++(ir_ports[x].rxHead) == BUFFERSIZE) {
                        ir_ports[x].rxHead = 0;
                    }
                }
            }
        } else {
            ir_ports[x].rxCount++;
        }
    }
}

void ir_period(void) {
    ir_tx();
    ir_rx();
}

void ir_send(ir_port* port, uint8_t data) {
    if (++(port->txHead) == BUFFERSIZE) {
        port->txHead = 0;
    }
    port->txBuffer[port->txHead] = data;
}

uint8_t ir_isReady(ir_port* port) {
    return port->rxHead != port->rxTail;
}

uint8_t ir_read(ir_port* port) {
    uint8_t b = port->rxBuffer[port->rxTail];
    if (++(port->rxTail) == BUFFERSIZE) {
        port->rxTail = 0;
    }
    return b;
}