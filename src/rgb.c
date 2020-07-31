#include "rgb.h"
#include "interrupts.h"

uint8_t rgbTickCounter;
void updateAnimations(void);



//TODO: verify correct pin
#define rgb_setHigh() (LATGbits.LATG3 = 1)
#define rgb_setLow() (LATGbits.LATG3 = 0)


#define delay60() asm("nop");
#define delay300() delay60() delay60() delay60() delay60() delay60()
#define delay600() delay300() delay300()
#define delay900() delay600() delay300()
    
//Gamma correction lookup table from https://learn.adafruit.com/led-tricks-gamma-correction/the-quick-fix
const uint8_t gamma8[] = {
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
    1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,
    2,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  5,  5,  5,
    5,  6,  6,  6,  6,  7,  7,  7,  7,  8,  8,  8,  9,  9,  9, 10,
   10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 14, 14, 15, 15, 16, 16,
   17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 24, 24, 25,
   25, 26, 27, 27, 28, 29, 29, 30, 31, 32, 32, 33, 34, 35, 35, 36,
   37, 38, 39, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 50,
   51, 52, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 66, 67, 68,
   69, 70, 72, 73, 74, 75, 77, 78, 79, 81, 82, 83, 85, 86, 87, 89,
   90, 92, 93, 95, 96, 98, 99,101,102,104,105,107,109,110,112,114,
  115,117,119,120,122,124,126,127,129,131,133,135,137,138,140,142,
  144,146,148,150,152,154,156,158,160,162,164,167,169,171,173,175,
  177,180,182,184,186,189,191,193,196,198,200,203,205,208,210,213,
  215,218,220,223,225,228,231,233,236,239,241,244,247,249,252,255 };

void rgb_init(void) {
    rgb_center = &rgb_leds[0];
    rgb_innerRing = &rgb_leds[1];
    rgb_outerRing = &rgb_leds[7];
    rgbTickCounter = 0;
}

void rgb_sendUpdate(void) {
    updateAnimations();
    //prepare all data
    uint8_t ledData[19*4];
    uint8_t ledBase = 0;
    uint8_t white;
    uint8_t x;
    for (x = 19; x > 0;) {
        
        uint8_t r, g, b;
        r = gamma8[rgb_leds[x].red];
        g = gamma8[rgb_leds[x].green];
        b = gamma8[rgb_leds[x].blue];

        x--;
        if (r < g) {
            white = r;
        } else {
            white = g;
        }
        if (b < white) {
            white = b;
        }
        ledData[ledBase] = g - white;
        ledData[ledBase+1] = r - white;
        ledData[ledBase+2] = b - white;
        ledData[ledBase+3] = white;
        ledBase += 4;
    }



    interrupts_disableGlobalInterrupts();
    //send it
    for(ledBase = 0; ledBase < 19; ledBase++) {
        for (x = 0; x < 4; x++) {
            for (uint8_t ledBit = 0x80; ledBit != 0; ledBit >>= 1) {
                if (ledData[ledBase+x] & ledBit) {
                    rgb_setHigh();
                    delay600();
                    rgb_setLow();
                    delay600();
                } else {
                    rgb_setHigh();
                    delay300();
                    rgb_setLow();
                    delay900();
                }
            }
        }
    }

    interrupts_enableGlobalInterrupts();
}


void rgb_setled(uint8_t led, uint8_t r, uint8_t g, uint8_t b) {
    rgb_leds[led].red = r;
    rgb_leds[led].green = g;
    rgb_leds[led].blue = b;
}

void rgb_tick(void) {
    rgbTickCounter++;
}
void rgb_animateled(uint8_t led, uint8_t r, uint8_t g, uint8_t b, uint16_t time) {
    rgb_leds[led].animation.r_s = rgb_leds[led].red;
    rgb_leds[led].animation.g_s = rgb_leds[led].green;
    rgb_leds[led].animation.b_s = rgb_leds[led].blue;
    rgb_leds[led].animation.r_e = r;
    rgb_leds[led].animation.g_e = g;
    rgb_leds[led].animation.b_e = b;
    rgb_leds[led].animation.time = time;
    rgb_leds[led].animation.elapsed = 0;
}
void updateAnimations() {
    for (uint8_t x = 0; x < 19; x++) {
        rgb_led* led = &rgb_leds[x];
        if (led->animation.time != 0) {
            led->animation.elapsed += rgbTickCounter;
            if (led->animation.elapsed >= led->animation.time) {
                led->red = led->animation.r_e;
                led->green = led->animation.g_e;
                led->blue = led->animation.b_e;
                led->animation.time = 0;
            } else {
                int16_t animAmount = (led->animation.elapsed / led->animation.time);
                led->red = led->animation.r_s + (((int16_t)(led->animation.r_s) - (int16_t)(led->animation.r_e)) * animAmount);
                led->green = led->animation.g_s + (((int16_t)(led->animation.g_s) - (int16_t)(led->animation.g_e)) * animAmount);
                led->blue = led->animation.b_s + (((int16_t)(led->animation.b_s) - (int16_t)(led->animation.b_e)) * animAmount);
            }
        }
    }

    rgbTickCounter = 0;
}

bool rgb_updateDue(void) {
    return rgbTickCounter >= (1000 / RGB_FPS);
}