#ifndef communications_h
#define communications_h

#include "common.h"
#include "ir.h"

#define MAX_MESSAGE_SIZE 2


typedef struct {
    uint8_t Buffer[MAX_MESSAGE_SIZE];
    uint8_t BufferPos;
    uint8_t State;
    uint8_t lastByte;
    uint8_t Id;
    ir_port* irPort;
} comms_port;

comms_port comms_ports[6];

#define MSG_Command 0x10
#define MSG_Ping 0x11
#define MSG_Pong 0x12

typedef struct {
    uint8_t value;
} MsgCommand, *pMsgCommand;

typedef struct {
    uint8_t value;
} MsgPing, *pMsgPing;

typedef struct {
    uint8_t value;
} MsgPong, *pMsgPong;


void comms_init(void);
void comms_poll(void);
void comms_sendMessage(comms_port* port, uint8_t msgType, uint8_t msg[], uint8_t length);


#endif