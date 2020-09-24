#include "matrixblocks.h"


bool millisecondPassed = false;

const uint8_t lights[360]={
  0, 0, 0, 0, 0, 1, 1, 2, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 15, 17, 18, 20, 22, 24, 26, 28, 30, 32, 35, 37, 39,
 42, 44, 47, 49, 52, 55, 58, 60, 63, 66, 69, 72, 75, 78, 81, 85, 88, 91, 94, 97, 101, 104, 107, 111, 114, 117, 121, 124, 127, 131, 134, 137,
141, 144, 147, 150, 154, 157, 160, 163, 167, 170, 173, 176, 179, 182, 185, 188, 191, 194, 197, 200, 202, 205, 208, 210, 213, 215, 217, 220, 222, 224, 226, 229,
231, 232, 234, 236, 238, 239, 241, 242, 244, 245, 246, 248, 249, 250, 251, 251, 252, 253, 253, 254, 254, 255, 255, 255, 255, 255, 255, 255, 254, 254, 253, 253,
252, 251, 251, 250, 249, 248, 246, 245, 244, 242, 241, 239, 238, 236, 234, 232, 231, 229, 226, 224, 222, 220, 217, 215, 213, 210, 208, 205, 202, 200, 197, 194,
191, 188, 185, 182, 179, 176, 173, 170, 167, 163, 160, 157, 154, 150, 147, 144, 141, 137, 134, 131, 127, 124, 121, 117, 114, 111, 107, 104, 101, 97, 94, 91,
 88, 85, 81, 78, 75, 72, 69, 66, 63, 60, 58, 55, 52, 49, 47, 44, 42, 39, 37, 35, 32, 30, 28, 26, 24, 22, 20, 18, 17, 15, 13, 12,
 11, 9, 8, 7, 6, 5, 4, 3, 2, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

uint8_t lastPing[6];
uint8_t lastPong[6];

void main(void) {
    config_init();
    button_init();
    rgb_init();
    status_init();
    ir_init();
    comms_init();
    interrupts_init();
    interrupts_enableGlobalInterrupts();

    for (uint8_t x = 0; x < 6; x++) {
        lastPong[x] = 200;
        lastPing[x] = 0;
    }

    status_setLed(0, true);
    
    while(true) {
        comms_poll();
        if (millisecondPassed) {
            millisecond();
            millisecondPassed = false;
        }
    }
}

void isr_millisecondTimer(void) {
    millisecondPassed = true;
}

uint8_t comCount = 0;

void millisecond() {
    rgb_tick();
    status_tick();
    button_tick();

    if (comCount++ == 200) {
        for (uint8_t x = 0; x < 6; x++) {
            status_setLed(x+1, lastPong[x] == lastPing[x]);
            MsgPing ping;
            lastPing[x]++;
            if (lastPing[x] == 200) {
                lastPing[x] = 0;
            }
            ping.value = lastPing[x];
            comms_sendMessage(&comms_ports[x], MSG_Ping, (uint8_t *)&ping, 1);
        }
    }
}



void HandleMessage(uint8_t side, uint8_t msgType, uint8_t msgbytes[], uint8_t msglength) {
    pMsgCommand pCommand;
    pMsgPing pPing;
    pMsgPong pPong;
    switch (msgType) {
        case MSG_Command:
            pCommand = (pMsgCommand)msgbytes;
            //Leds.Blue = pCommand->value ? 255 : 0;
            break;
        case MSG_Ping:
            pPing = (pMsgPing)msgbytes;
            MsgPong pong;
            pong.value = pPing->value;
            comms_sendMessage(&comms_ports[side-1], MSG_Pong, (uint8_t *)&pong, 1);
            break;
        case MSG_Pong:
            pPong = (pMsgPong)msgbytes;
            lastPong[side-1] = pPong->value;
            break;
    }
}