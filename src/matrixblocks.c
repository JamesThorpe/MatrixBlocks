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


void main(void) {
    config_init();
    button_init();
    rgb_init();
    status_init();
    interrupts_init();
    interrupts_enableGlobalInterrupts();

    
    status_setLed(0, true);
    
   
    /*status_animateLed(1, 200, 800);
    status_animateLed(2, 300, 700);
    status_animateLed(3, 400, 600);
    status_animateLed(4, 500, 500);
    status_animateLed(5, 600, 400);
    status_animateLed(6, 700, 300);*/
    
    /*
    for (uint8_t x = 0; x < 18; x++) {
        if (x%3 == 0) {
            rgb_setled(x, 255, 0, 0);
        } else if (x%3 == 1) {
            rgb_setled(x, 0, 255, 0);
        } else {
            rgb_setled(x, 0, 0, 255);
        }
    }
    rgb_setled(18, 100, 100, 100);*/

    while(true) {
        if (millisecondPassed) {
            millisecond();
            millisecondPassed = false;
        }

        /*for (uint8_t x = 0; x < 6; x++) {
            if (button_isPressed(&buttons[x])) {
                rgb_setled(x+1, 0, 0, 255);
                rgb_animateled(x+1, 255, 0, 0, 2000);
                rgb_animateled(x+1, 0, 255, 0, 1000);
                if (status_leds[x + 1].counter == 0) {
                    status_animateLed(x + 1, 800, 200);
                } else {
                    status_setLed(x + 1, false);
                }
            }
        }*/
    }
}


void isr_millisecondTimer(void) {
    millisecondPassed = true;
}

int lc = 0;
int c = 0;
int txc = 0;

void millisecond() {
    rgb_tick();
    status_tick();
    button_tick();

    txc++;
    if (txc == 500) {
        LATAbits.LATA0 = 1;
        LATAbits.LATA1 = 1;
    } else if (txc == 1000) {
        LATAbits.LATA0 = 0;
        LATAbits.LATA1 = 0;
        txc = 0;
    }

    if (PORTF & (1 << 7)) {
        status_setLed(1, true);
    } else {
        status_setLed(1, false);
    }

    if (PORTF & (1 << 6)) {
        status_setLed(2, true);
    } else {
        status_setLed(2, false);
    }

    /*
    if (button_isDown(button1)) {
        for (uint8_t bx = 0; bx < 19; bx++) {
            rgb_setled(bx, 255, 255, 255);
        }
    } else if (button_isReleased(button1)) {
        for (uint8_t bx = 0; bx < 19; bx++) {
            rgb_animateled(bx, 255, 0, 0, 200);
            rgb_animateled(bx, 0, 255, 0, 200);
            rgb_animateled(bx, 0, 0, 255, 200);
        }
    }else {*/
        c++;
        if (c == 9) {
            c = 0;
            lc++;
            int lcx;
            uint8_t x;
            uint8_t r, g, b;


            g = lights[lc%360];

            rgb_setled(0, g, g, g);

            for (x = 7; x < 19; x++) {
                lcx = lc + ((x-7)*30);
                r = lights[((lcx%360)+120)%360];
                g = lights[lcx%360];
                b = lights[((lcx%360)+240)%360];

                rgb_setled(x, r, g, b);
            }
           
            if (lc == 360) {
                lc = 0;
            }

        }
    /*}*/

    
    //TODO: this should be done in the IR code when not transmitting
    if (rgb_updateDue()) {
        rgb_sendUpdate();
    }
}