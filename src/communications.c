#include "communications.h"
#include "matrixblocks.h"

#define STATE_WAITINGSTART 1
#define STATE_INMESSAGE 2
#define STATE_AFTERESCAPE 3

#define FRAMESTART 0xFE
#define FRAMEEND 0xFD
#define FRAMEESCAPE 0xFC
#define FRAMENOP 0xFB

void comms_initialisePort(uint8_t x, comms_port* port, ir_port* irport)
{
    port->Id = x;
    port->State = STATE_WAITINGSTART;
    port->BufferPos = 0;
    port->lastByte = 0;
    port->irPort = irport;
}

void comms_init(void) {
    for (uint8_t x = 0; x < 6; x++) {
        comms_initialisePort(x+1, &comms_ports[x], &ir_ports[x]);
    }
}

void comms_checkComms(comms_port* port)
{
    uint8_t data;
    int8_t isready = ir_isReady(port->irPort);
    while (isready) {
        data = ir_read(port->irPort);
        if (port->State == STATE_WAITINGSTART && data == FRAMESTART) {
            port->State = STATE_INMESSAGE;
        } else if (port->State == STATE_INMESSAGE) {
            if (data == FRAMEESCAPE) {
                port->State = STATE_AFTERESCAPE;
            } else if (data == FRAMESTART) {
                //new frame, not expected - start again
                port->BufferPos = 0;
            } else {
                if (data == FRAMENOP) {
                    //ignore
                } else if (data != FRAMEEND) {
                    port->Buffer[port->BufferPos++] = data;
                } else {
                    HandleMessage(port->Id, port->Buffer[0], &(port->Buffer[1]), port->BufferPos - 1);
                    port->BufferPos = 0;
                }
            }
        } else if (port->State == STATE_AFTERESCAPE) {
            port->Buffer[port->BufferPos++] = data ^ 0x20;
        }
        isready = ir_isReady(port->irPort);
    }
    
}

void comms_poll(void) {
    comms_checkComms(&comms_ports[0]);
    comms_checkComms(&comms_ports[1]);
    comms_checkComms(&comms_ports[2]);
    comms_checkComms(&comms_ports[3]);
    comms_checkComms(&comms_ports[4]);
    comms_checkComms(&comms_ports[5]);
}

void WriteByte(comms_port* port, uint8_t data) {
    if (port->lastByte == data) {
        ir_send(port->irPort, FRAMENOP);
        ir_send(port->irPort, data);
    } else {
        port->lastByte = data;
        ir_send(port->irPort, data);
    }
}

void comms_sendMessage(comms_port* port, uint8_t msgType, uint8_t msg[], uint8_t length) {
    WriteByte(port, FRAMESTART);
    if (msgType == FRAMESTART || msgType == FRAMEEND || msgType == FRAMEESCAPE || msgType == FRAMENOP) {
        WriteByte(port, FRAMEESCAPE);
        WriteByte(port, msgType ^ 0x20);
    } else {
        WriteByte(port, msgType);
    }
    for (uint8_t i = 0; i < length; i++) {
        if (msg[i] == FRAMESTART || msg[i] == FRAMEEND || msg[i] == FRAMEESCAPE || msgType == FRAMENOP) {
            WriteByte(port, FRAMEESCAPE);
            WriteByte(port, msg[i] ^ 0x20);
        } else {
            WriteByte(port, msg[i]);
        }
    }
    WriteByte(port, FRAMEEND);
}